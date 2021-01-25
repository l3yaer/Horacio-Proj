#include "BetaMemoryNode.h"
#include "Tuple.h"

void BetaMemoryNode::propagate_assert(TupleFactList *object, WorkingMemory *memory)
{
	if(object->count == 0) return;
	DualMemory<Tuple *, Fact *> *tuple_memory = memory->get_memory(this);
	std::vector<Tuple *> to_assert;
	TupleFactList::Iterator it = object->iterator();
	while(it.next())
	{
		Tuple *tuple = new Tuple(memory->next_tuple_id(), *it.tuple, *it.fact);
		tuple->group = (*it.tuple)->id;
		to_assert.push_back(tuple);
	}
	propagate_assert_internal(to_assert, memory, tuple_memory);
}

void BetaMemoryNode::propagate_update(TupleFactList *object, WorkingMemory *memory)
{
	if(object->count == 0) return;
	DualMemory<Tuple *, Fact *> *tuple_memory = memory->get_memory(this);
	std::vector<Tuple *> to_update;
	std::vector<Tuple *> to_assert;
	TupleFactList::Iterator it = object->iterator();
	while(it.next())
	{
		Tuple *child = tuple_memory->find(*it.tuple, *it.fact);
		if(child == nullptr)
		{
			child = new Tuple(memory->next_tuple_id(), *it.tuple, *it.fact);
			child->group = (*it.tuple)->id;
			to_assert.push_back(child);
		}
		else
		{
			to_update.push_back(child);
		}
	}
	propagate_assert_internal(to_assert, memory, tuple_memory);
	propagate_update_internal(to_update, memory, tuple_memory);
}

void BetaMemoryNode::propagate_retract(TupleFactList *object, WorkingMemory *memory)
{
	if(object->count == 0) return;
	DualMemory<Tuple *, Fact *> *tuple_memory = memory->get_memory(this);
	std::vector<Tuple *> to_retract;
	TupleFactList::Iterator it = object->iterator();
	while(it.next())
	{
		Tuple *child = tuple_memory->find(*it.tuple, *it.fact);
		if(child != nullptr)
			to_retract.push_back(child);
	}
	propagate_retract_internal(to_retract, memory, tuple_memory);
}

std::vector<Tuple *> BetaMemoryNode::get_source(WorkingMemory *memory)
{
	return memory->get_memory(this)->data();
}

void BetaMemoryNode::attach(ObjectSink<std::vector<Tuple *>> *sink)
{
	sinks.push_back(sink);
}

void BetaMemoryNode::propagate_assert_internal(std::vector<Tuple *> object, WorkingMemory *memory, DualMemory<Tuple *, Fact *> *tuple_memory)
{
	if(object.empty()) return;

	for(auto sink : sinks)
		sink->propagate_assert(object, memory);

	for(auto tuple : object)
		tuple_memory->add(tuple);
}

void BetaMemoryNode::propagate_update_internal(std::vector<Tuple *> object, WorkingMemory *memory, DualMemory<Tuple *, Fact *> *tuple_memory)
{
	if(object.empty()) return;

	for(auto sink : sinks)
		sink->propagate_update(object, memory);
}

void BetaMemoryNode::propagate_retract_internal(std::vector<Tuple *> object, WorkingMemory *memory, DualMemory<Tuple *, Fact *> *tuple_memory)
{
	if(object.empty()) return;

	for(auto sink : sinks)
		sink->propagate_retract(object, memory);

	for(auto tuple : object)
		tuple_memory->remove(tuple);
}
