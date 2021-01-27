#include "Rete.h"
#include <iostream>

using namespace Rete;

void AlphaMemory::activate(WME *wme)
{
	items.push_front(wme);
	for(auto node : successors)
		node->alpha_activation(wme);
}

Token::Token(WME *wme, Token *parent)
	: wme(wme), parent(parent)
{
	if(parent == nullptr)
		token_index = 0;
	else
		token_index = parent->token_index + 1;
}

WME *Token::index(int index) const
{
	if(index == token_index)
		return wme;
	return parent->index(index);
}

void BetaMemory::join_activation(Token *token, WME *wme)
{
	Token *new_token = new Token(wme, token);
	items.push_front(new_token);
	for (auto child : children)
		child->beta_activation(token);
}

void BetaMemory::update_new()
{
	JoinNode *join = parent;
	std::vector<BetaMemory *> saved_children = join->children;
	join->children = { this };

	for(auto wme : join->alpha_src->items)
		join->alpha_activation(wme);

	join->children = saved_children;
}

bool TestAtJoinNode::operator==(const TestAtJoinNode &rhs) const
{
	return first_field_arg == rhs.first_field_arg &&
		second_field_arg == rhs.second_field_arg &&
		index_second_token_arg == rhs.index_second_token_arg;
}

JoinNode::JoinNode()
	: alpha_src(nullptr), beta_src(nullptr)
{}

void JoinNode::alpha_activation(WME *wme)
{
	if(beta_src)
		for(auto token : beta_src->items)
		{
			if(test(token, wme))
				for(auto child : children)
					child->join_activation(token, wme);
		}
	else
		for(auto child : children)
			child->join_activation(nullptr, wme);
}

void JoinNode::beta_activation(Token *token)
{
	for(auto wme : alpha_src->items)
	{
		if(test(token, wme))
			for(auto child : children)
				child->join_activation(token, wme);
	}
}

bool JoinNode::test(Token *token, WME *wme) const
{
	if(beta_src == nullptr)
		return true;
	for(auto test : tests)
	{
		std::string arg1 = wme->get(test.first_field_arg);
		WME *wme2 = token->index(test.index_second_token_arg);
		std::string arg2 = wme2->get(test.second_field_arg);
		if(arg1 != arg2)
			return false;
	}
	return true;
}

void ProductionNode::join_activation(Token *token, WME *wme)
{
	Token *new_token = new Token(wme, token);
	items.push_back(new_token);
}

CField CField::var(const std::string &value)
{
	return {CField::Type::VARIABLE, value};
}

CField CField::cons(const std::string &value)
{
	return {CField::Type::CONSTANT, value};
}

Condition::Condition(CField id, CField attr, CField value)
{
	fields[0] = id;
	fields[1] = attr;
	fields[2] = value;
}

Condition::Condition(const std::string &id, const std::string &attr, const std::string &value)
{
	fields[0] = StringManip::starts_with(id, "?") ? CField::var(id.substr(1)) : CField::cons(id);
	fields[1] = StringManip::starts_with(attr, "?") ? CField::var(attr.substr(1)) : CField::cons(attr);
	fields[2] = StringManip::starts_with(value, "?") ? CField::var(value.substr(1)) : CField::cons(value);
}

bool Condition::is_satisfied(const WME *wme) const
{
	for(int i = 0; i < WME::Field::COUNT; ++i)
		if(fields[i].type == CField::Type::CONSTANT &&
		   fields[i].value != wme->get(i))
			return false;
	return true;
}

ConstTestNode::ConstTestNode(WME::Field field, const std::string &value, AlphaMemory *output)
	: field(field), value(value), output(output)
{}

ConstTestNode *ConstTestNode::dummy()
{
	return new ConstTestNode(WME::Field::NONE, "", nullptr);
}

bool ConstTestNode::activate(WME *wme)
{
	if(field != WME::Field::NONE && wme->get(field) != value)
		return false;

	if(output != nullptr)
		output->activate(wme);

	for(auto child : children)
		child->activate(wme);

	return true;
}

Net::Net()
	: dummy(ConstTestNode::dummy())
{
	const_test_nodes.push_back(std::unique_ptr<ConstTestNode>(dummy));
}

void Net::add(WME *wme)
{
	working_memory.push_back(std::unique_ptr<WME>(wme));
	dummy->activate(wme);
}

BetaMemory *Net::build_beta_memory(JoinNode *parent)
{
	for(auto child : parent->children)
		return child;

	BetaMemory *memory = new BetaMemory;
	beta_memories.push_back(std::unique_ptr<BetaMemory>(memory));
	memory->parent = parent;
	parent->children.push_back(memory);
	memory->update_new();
	return memory;
}

JoinNode *Net::build_join_node(BetaMemory *beta_memory, AlphaMemory *alpha_memory, const std::vector<TestAtJoinNode> &tests)
{
	JoinNode *node = new JoinNode;
	join_nodes.push_back(std::unique_ptr<JoinNode>(node));
	node->beta_src = beta_memory;
	node->alpha_src = alpha_memory;
	node->tests = tests;
	alpha_memory->successors.push_front(node);
	if(beta_memory != nullptr)
		beta_memory->children.push_back(node);
	return node;
}

void Net::lookup_conditions(const std::vector<Condition> &conditions, const std::string value, int *index, int *field)
{
	*index = 0;

	for(auto condition : conditions)
	{
		for(int i = 0; i < WME::Field::COUNT; ++i)
		{
			if(condition.fields[i].type == CField::Type::VARIABLE &&
				condition.fields[i].value == value)
			{
				*field = i;
				return;
			}
		}
		(*index)++;
	}

	*index = -1;
	*field = -1;
}

ConstTestNode *Net::build_const_node(ConstTestNode *parent, WME::Field field, const std::string &symbol)
{
	for(auto child : parent->children)
		if(child->field == field && child->value == symbol)
			return child;

	ConstTestNode *node = new ConstTestNode(field, symbol, nullptr);
	const_test_nodes.push_back(std::unique_ptr<ConstTestNode>(node));
	parent->children.push_back(node);
	return node;
}

std::vector<TestAtJoinNode> Net::get_tests(const Condition &condition,const std::vector<Condition> &prev_conditions)
{
	std::vector<TestAtJoinNode> tests;

	for(int i = 0; i < WME::Field::COUNT; ++i)
	{
		if(condition.fields[i].type != CField::Type::VARIABLE)
			continue;

		std::string value = condition.fields[i].value;
		int index;
		int field;
		lookup_conditions(prev_conditions, value, &index, &field);
		if(index == -1)
			continue;

		TestAtJoinNode test_node;
		test_node.first_field_arg = static_cast<WME::Field>(i);
		test_node.index_second_token_arg = index;
		test_node.second_field_arg = static_cast<WME::Field>(field);
		tests.push_back(test_node);
	}

	return tests;
}

AlphaMemory *Net::build_alpha(const Condition &condition)
{
	ConstTestNode *current = dummy;
	for(int i = 0; i < WME::Field::COUNT; ++i)
		if(condition.fields[i].type == CField::CONSTANT)
			current = build_const_node(current, static_cast<WME::Field>(i), condition.fields[i].value);

	if(current->output != nullptr)
		return current->output;

	current->output = new AlphaMemory;
	alpha_memories.push_back(std::unique_ptr<AlphaMemory>(current->output));

	for(auto &wme : working_memory)
		if(condition.is_satisfied(wme.get()))
			current->output->activate(wme.get());

	return current->output;
}

ProductionNode *Net::add(const std::vector<Condition> &lhs, const std::string &rhs)
{
	std::vector<Condition> early_conditions;

	std::vector<TestAtJoinNode> tests = get_tests(lhs[0], early_conditions);
	AlphaMemory *alpha_memory = build_alpha(lhs[0]);
	BetaMemory *beta_memory = nullptr;
	JoinNode *join_node = build_join_node(beta_memory, alpha_memory, tests);
	early_conditions.push_back(lhs[0]);

	for(size_t i = 1; i < lhs.size(); ++i)
	{
		beta_memory = build_beta_memory(join_node);
		tests = get_tests(lhs[i], early_conditions);
		alpha_memory = build_alpha(lhs[i]);
		join_node = build_join_node(beta_memory, alpha_memory, tests);
		early_conditions.push_back(lhs[i]);
	}

	ProductionNode *production_node = new ProductionNode;
	production_nodes.push_back(std::unique_ptr<ProductionNode>(production_node));
	production_node->parent = join_node;
	production_node->rhs = rhs;
	join_node->children.push_back(production_node);
	production_node->update_new();
	return production_node;
}
