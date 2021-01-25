#include "AlphaMemoryNode.h"

void AlphaMemoryNode::propagate_assert(std::vector<Fact*> object, WorkingMemory *memory)
{
	Memory<Fact *> *fact_memory = memory->get_memory(this);
	for(auto sink : sinks)
		sink->propagate_assert(object, memory);

	for(auto fact : object)
		fact_memory->add(fact);
}

void AlphaMemoryNode::propagate_update(std::vector<Fact*> object, WorkingMemory *memory)
{
	std::vector<Fact*> to_assert, to_update;
	Memory<Fact *> *fact_memory = memory->get_memory(this);
	for(auto fact : object)
		if(fact_memory->contains(fact))
			to_update.push_back(fact);
		else
			to_assert.push_back(fact);

	if(!to_update.empty())
		for(auto sink : sinks)
			sink->propagate_update(to_update, memory);

	if(!to_assert.empty())
		propagate_assert(to_assert, memory);
}

void AlphaMemoryNode::propagate_retract(std::vector<Fact*> object, WorkingMemory *memory)
{
	std::vector<Fact *> to_retract;
	Memory<Fact *> *fact_memory = memory->get_memory(this);
	for(auto fact : object)
		if(fact_memory->contains(fact))
			to_retract.push_back(fact);

	if(!to_retract.empty())
	{
		for(auto sink : sinks)
			sink->propagate_retract(to_retract, memory);

		for(auto fact : to_retract)
			fact_memory->remove(fact);
	}
}

std::vector<Fact*> AlphaMemoryNode::get_source(WorkingMemory *memory)
{
	return memory->get_memory(this)->data();
}

void AlphaMemoryNode::attach(ObjectSink<std::vector<Fact*>> *sink)
{
	sinks.push_back(sink);
}
