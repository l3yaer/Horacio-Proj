#ifndef _BETANODE_H_
#define _BETANODE_H_

#include "ObjectSink.h"
#include "WorkingMemory.h"
#include "ReteVisitor.h"

class Tuple;

class BetaNode : public ObjectSink<Tuple *>,  public ReteVisitableImpl<BetaNode>
{
protected:
	BetaNode() {};
public:
	BetaMemoryNode *memory_node;

	virtual void propagate_assert(std::vector<Fact*> objects, WorkingMemory *memory) override;
	virtual void propagate_update(std::vector<Fact*> objects, WorkingMemory *memory) override;
	virtual void propagate_retract(std::vector<Fact*> objects, WorkingMemory *memory) override;
};

#endif //_BETANODE_H_
