#ifndef _ALPHAMEMORYNODE_H_
#define _ALPHAMEMORYNODE_H_

#include <vector>
#include "AlphaMemory.h"
#include "ObjectSink.h"
#include "WorkingMemory.h"
#include "ReteVisitor.h"

class AlphaMemoryNode : public ObjectSink<std::vector<Fact *>>, public ObjectSource<std::vector<Fact *>>, public ReteVisitableImpl<AlphaMemoryNode>
{
public:
	std::vector<ObjectSink<std::vector<Fact *>> *> sinks;

	void propagate_assert(std::vector<Fact*> object, WorkingMemory *memory) override;
	void propagate_update(std::vector<Fact*> object, WorkingMemory *memory) override;
	void propagate_retract(std::vector<Fact*> object, WorkingMemory *memory) override;

	std::vector<Fact*> get_source(WorkingMemory *memory) override;
	void attach(ObjectSink<std::vector<Fact*>> *sink) override;
};

#endif //_ALPHAMEMORYNODE_H_
