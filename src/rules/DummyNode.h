#ifndef _DUMMYNODE_H_
#define _DUMMYNODE_H_

#include "ReteNode.h"

class DummyNode : public ReteNode
{
public:
	DummyNode();
	void clear() override;
	const TokenVector &get_output() override;
};

#endif //_DUMMYNODE_H_
