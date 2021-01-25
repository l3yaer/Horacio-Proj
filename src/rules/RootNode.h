#ifndef _ROOTNODE_H_
#define _ROOTNODE_H_

#include "AlphaNode.h"

class RootNode : public AlphaNode, public ReteVisitableImpl<RootNode>
{
public:
	bool is_satisfied(Fact *fact, Memory<Fact *> memory) const override
	{
		return true;
	}
};

#endif //_ROOTNODE_H_
