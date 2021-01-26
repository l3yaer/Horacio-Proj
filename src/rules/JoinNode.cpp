#include "JoinNode.h"

JoinNode::JoinNode(ReteNodePtr left_parent, AlphaNodePtr right_parent, const TestNodeVector &tests, const Condition &condition)
	: BetaNode(left_parent, right_parent, tests)
{
	positive = condition.get_type() == Condition::Type::POSITIVE;
}

const TokenVector &JoinNode::get_output()
{
	if(!ready_for_output)
	{
		for (auto token : left_parent->get_output()) {
			if(positive)
			{
				for (auto wme : right_parent->get_output()) {
					if(check_pass_all_tests(token, wme))
					{
						output.push_back(token);
						output.back().push_back(wme);
					}
				}
			}
			else
			{
				if(check_pass_none_tests(token))
				{
					output.push_back(token);
					output.back().push_back({"#", "#", "#"});
				}
			}
		}
		ready_for_output = true;
	}
	return output;
}

bool JoinNode::check_pass_all_tests(const Token &token, const MemoryElement &wme)
{
	for (auto test : tests) {
		if(!test.test(token, wme))
			return false;
	}
	return true;
}

bool JoinNode::check_pass_none_tests(const Token &token)
{
	for (auto wme : right_parent->get_output()) {
		for (auto test : tests) {
			if(test.test(token, wme))
				return false;
		}
	}
	return true;
}
