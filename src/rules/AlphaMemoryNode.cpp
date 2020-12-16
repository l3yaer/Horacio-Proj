#include "AlphaMemoryNode.h"

void AlphaMemoryNode::propagate_assert(std::vector<Fact*> objects, Memory<Fact*> memory)
{
	for(auto sink : sinks)
		sink->propagate_assert(objects, memory);

	for(auto fact : objects)
		memory.add(fact);
}

void AlphaMemoryNode::propagate_update(std::vector<Fact*> objects, Memory<Fact*> memory)
{
	std::vector<Fact*> to_assert, to_update;
	for(auto fact : objects)
		if(memory.contains(fact))
			to_update.push_back(fact);
		else
			to_assert.push_back(fact);

	if(!to_update.empty())
		for(auto sink : sinks)
			sink->propagate_update(to_update, memory);

	if(!to_assert.empty())
		propagate_assert(to_assert, memory);
}

void AlphaMemoryNode::propagate_retract(std::vector<Fact*> objects, Memory<Fact*> memory)
{
	std::vector<Fact *> to_retract;
	for(auto fact : objects)
		if(memory.contains(fact))
			to_retract.push_back(fact);

	if(!to_retract.empty())
	{
		for(auto sink : sinks)
			sink->propagate_retract(to_retract, memory);

		for(auto fact : to_retract)
			memory.remove(fact);
	}
}

std::vector<Fact*> AlphaMemoryNode::get_source(Memory<Fact*> memory)
{
	return memory.data();
}

void AlphaMemoryNode::attach(ObjectSink<Fact*> *sink)
{
	sinks.push_back(sink);
}
