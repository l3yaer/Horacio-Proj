#ifndef _JOINNODE_H_
#define _JOINNODE_H_

#include "BetaNode.h"
#include "Condition.h"

class JoinNode : public BetaNode
{
public:
	JoinNode(ReteNodePtr left_parent, AlphaNodePtr right_parent, const TestNodeVector &tests, const Condition &condition);
	const TokenVector &get_output() override;
private:
	bool positive;
	bool check_pass_all_tests(const Token &token, const MemoryElement &wme);
	bool check_pass_none_tests(const Token &token);
};

#endif //_JOINNODE_H_
