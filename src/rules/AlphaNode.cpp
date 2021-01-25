#include "AlphaNode.h"

void AlphaNode::propagate_assert(std::vector<Fact*> objects, WorkingMemory *memory)
{
	std::vector<Fact *> to_assert;
	for(auto fact : objects)
		if(is_satisfied(fact, memory))
			to_assert.push_back(fact);

	if(!to_assert.empty())
	{
		for(auto child : children)
			child->propagate_assert(to_assert, memory);

		if(memory_node != nullptr)
			memory_node->propagate_assert(to_assert, memory);
	}
}

void AlphaNode::propagate_update(std::vector<Fact*> objects, WorkingMemory *memory)
{
	std::vector<Fact *> to_update, to_retract;


	for(auto fact : objects)
		if(is_satisfied(fact, memory))
			to_update.push_back(fact);
		else
			to_retract.push_back(fact);

	internal_propagate_retract(to_retract, memory);
	internal_propagate_update(to_update, memory);
}

void AlphaNode::propagate_retract(std::vector<Fact*> objects, WorkingMemory *memory)
{
	internal_propagate_retract(objects, memory);
}

void AlphaNode::internal_propagate_update(std::vector<Fact*> objects, WorkingMemory *memory)
{
	if(objects.empty()) return;

	for(auto child : children)
		child->propagate_update(objects, memory);

	if(memory_node != nullptr)
		memory_node->propagate_update(objects, memory);
}

void AlphaNode::internal_propagate_retract(std::vector<Fact*> objects, WorkingMemory *memory)
{
	if(objects.empty()) return;

	for(auto child : children)
		child->propagate_retract(objects, memory);

	if(memory_node != nullptr)
		memory_node->propagate_retract(objects, memory);
}
