#ifndef _TOKENFILTERNODE_H_
#define _TOKENFILTERNODE_H_

#include <functional>
#include <unordered_map>
#include <string>
#include "BetaNode.h"
#include "Condition.h"

class TokenFilterNode : public BetaNode
{
public:
	class Test
	{
	public:
		using JudgeFunc = std::function<bool(const std::string &, const std::string&)>;
		bool test(const Condition &c);
		bool need_filter(const Condition &c);
		void insert_judge_func(const std::string &key, JudgeFunc &value);
	private:
		std::unordered_map<std::string, JudgeFunc> funcs;
	};

	TokenFilterNode(ReteNodePtr left_parent, AlphaNodePtr right_parent, const TestNodeVector &tests, const Condition &condition, Test &test_token);
	const TokenVector &get_output() override;

private:
	Condition condition;
	bool positive;
	Test &test_token;
};

#endif //_TOKENFILTERNODE_H_
