#include "TokenFilterNode.h"

TokenFilterNode::TokenFilterNode(ReteNodePtr left_parent, AlphaNodePtr right_parent, const TestNodeVector &tests, const Condition &condition, Test &test_token)
	: BetaNode(left_parent, right_parent, tests), condition(condition), test_token(test_token)
{
	positive = condition.get_type() == Condition::Type::POSITIVE;
}

const TokenVector &TokenFilterNode::get_output()
{
	if(!ready_for_output)
	{
		for (auto token : left_parent->get_output()) {
			for (auto test : tests) {
				condition.set(test.first_arg_field,
							  token.at(test.second_arg_cond_num).get(test.second_arg_field));
			}
			if((positive ^ test_token.test(condition)) == 0)
			{
				output.push_back(token);
				output.back().push_back({
						condition.get(Triple::Field::ID),
						(positive ? "" : "~") + condition.get(Triple::Field::ATTR),
						condition.get(Triple::Field::VALUE)
					});
			}
		}
		ready_for_output = true;
	}
	return output;
}

bool TokenFilterNode::Test::test(const Condition &c)
{
	auto it = funcs.find(c.get(Triple::Field::ATTR));
	return it->second(c.get(Triple::Field::ID), c.get(Triple::Field::VALUE));
}

bool TokenFilterNode::Test::need_filter(const Condition &c)
{
	std::string attr = c.get(Triple::Field::ATTR);
	if(!attr.empty() && attr.at(0) != '.')
		return true;
	return false;
}

void TokenFilterNode::Test::insert_judge_func(const std::string &key, JudgeFunc &value)
{
	funcs.insert(std::make_pair(key, value));
}
