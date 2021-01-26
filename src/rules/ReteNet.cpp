#include <string>
#include <iostream>
#include "ReteNet.h"
#include "DummyNode.h"
#include "JoinNode.h"

ReteNet::ReteNet()
	: dummy_node(std::make_shared<DummyNode>())
{}

void ReteNet::add(const ConditionVector &lhs, const ConditionVector &rhs)
{
	ReteNodePtr current_node = build_network_for_conditions(dummy_node, lhs, {});
	result_nodes.insert(std::make_shared<ProductionNode>(current_node, lhs, rhs));
}

std::vector<ConditionVector> ReteNet::run()
{
	std::vector<ConditionVector> ret;
	for (auto node : result_nodes) {
		std::vector<ConditionVector> infos = node->get_output_infos();
		std::copy(infos.begin(), infos.end(), std::back_inserter(ret));
	}
	return ret;
}

void ReteNet::clear()
{
	for (auto node : result_nodes) {
		node->clear();
	}
}

void ReteNet::add(const MemoryElement &wme)
{
	std::vector<std::vector<std::string>> vt =
	{
		{wme.get(Triple::Field::ID), "*"},
		{wme.get(Triple::Field::ATTR), "*"},
		{wme.get(Triple::Field::VALUE), "*"},

	};

	for (auto id : vt.at(0))
		for (auto attr : vt.at(1))
			for (auto value : vt.at(2))
			{
				auto it = condition_to_alpha.find(Condition(id, attr, value));
				if(it != condition_to_alpha.end())
				   it->second->add(wme);
			}
}

void ReteNet::add(const std::string &key, TokenFilterNode::Test::JudgeFunc judge_function)
{
	token_filter_test_node.insert_judge_func(key, judge_function);
}

ReteNodePtr ReteNet::build_token_filter_node(ReteNodePtr parent, AlphaNodePtr alpha_mem, TestNodeVector tests, const Condition &condition)
{
	NetGroup node = {parent, alpha_mem, tests, condition};
	auto it = nodes.find(node);
	if(it == nodes.end())
	{
		ReteNodePtr ret = std::make_shared<TokenFilterNode>(parent, alpha_mem, tests, condition, token_filter_test_node);
		nodes[node] = ret;
		return ret;
	}
	else
		return it->second;
}

ReteNodePtr ReteNet::build_join_node(ReteNodePtr parent, AlphaNodePtr alpha_mem, TestNodeVector tests, const Condition &condition)
{
	NetGroup node = {parent, alpha_mem, tests, condition};
	auto it = nodes.find(node);

	if(it == nodes.end())
	{
		ReteNodePtr ret = std::make_shared<JoinNode>(parent, alpha_mem, tests, condition);
		nodes[node] = ret;
		return ret;
	}
	else
		return it->second;
}

ReteNodePtr ReteNet::build_network_for_conditions(ReteNodePtr parent, const ConditionVector &conditions, ConditionVector high_conditions)
{
	for (auto&& c : conditions) {
		auto&& tests = tests_from_conditions(c, high_conditions);
		auto&& am = build_alpha_node(c);
		if (token_filter_test_node.need_filter(c)) {
			parent = build_token_filter_node(parent, am, tests, c);
		}
		else {
			parent = build_join_node(parent, am, tests, c);
		}
		high_conditions.push_back(c);
	}
	return parent;
}

AlphaNodePtr ReteNet::build_alpha_node(const Condition &condition)
{
	Condition index = condition.index();
	if(condition_to_alpha.count(index) == 0)
		return condition_to_alpha[index] = std::make_shared<AlphaNode>();
	return condition_to_alpha[index];
}

TestNodeVector ReteNet::tests_from_conditions(Condition condition, const ConditionVector &high_conditions)
{
	TestNodeVector ret;
	TestNodeVector tests = TestNode::generate(condition, high_conditions);
	std::copy(tests.begin(), tests.end(), std::back_inserter(ret));
	return ret;
}

bool NetGroup::operator==(const NetGroup &rhs) const
{
	return *parent == *rhs.parent &&
		tests == rhs.tests &&
		*alpha_memory == *rhs.alpha_memory &&
		condition == rhs.condition;
}
