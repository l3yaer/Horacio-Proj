#ifndef _BETANODE_H_
#define _BETANODE_H_

#include "ReteNode.h"
#include "AlphaNode.h"
#include "TestNode.h"

class BetaNode : public ReteNode
{
public:
	BetaNode(ReteNodePtr left_parent, AlphaNodePtr right_parent, const TestNodeVector &tests);
	void clear() override;
protected:
	ReteNodePtr left_parent;
	AlphaNodePtr right_parent;
	TestNodeVector tests;
};

#endif //_BETANODE_H_
