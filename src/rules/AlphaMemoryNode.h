#ifndef _ALPHAMEMORYNODE_H_
#define _ALPHAMEMORYNODE_H_

#include <vector>
#include "AlphaMemory.h"
#include "ObjectSink.h"


class AlphaMemoryNode : public FactSink, public FactSource
{
public:
	std::vector<FactSink *> sinks;

	void propagate_assert(std::vector<Fact*> objects, Memory<Fact*> memory) override;
	void propagate_update(std::vector<Fact*> objects, Memory<Fact*> memory) override;
	void propagate_retract(std::vector<Fact*> objects, Memory<Fact*> memory) override;

	std::vector<Fact*> get_source(Memory<Fact*> memory) override;
	void attach(ObjectSink<Fact*> *sink) override;
};

#endif //_ALPHAMEMORYNODE_H_
