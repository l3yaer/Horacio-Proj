#ifndef _ROOTNODE_H_
#define _ROOTNODE_H_

#include "AlphaNode.h"

class RootNode : public AlphaNode
{
public:
	bool is_satisfied(Fact *fact, Memory<Fact *> memory) const override
	{
		return true;
	}
};

#endif //_ROOTNODE_H_
