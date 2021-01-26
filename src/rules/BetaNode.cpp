#include "BetaNode.h"

BetaNode::BetaNode(ReteNodePtr left_parent, AlphaNodePtr right_parent, const TestNodeVector &tests)
	: ReteNode(false), left_parent(left_parent), right_parent(right_parent), tests(tests)
{
}

void BetaNode::clear()
{
	if(ready_for_output)
	{
		ready_for_output = false;
		output.clear();
		left_parent->clear();
		right_parent->clear();
	}
}
