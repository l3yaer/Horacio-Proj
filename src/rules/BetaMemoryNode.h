#ifndef _BETAMEMORYNODE_H_
#define _BETAMEMORYNODE_H_

#include <vector>
#include "ObjectSink.h"
#include "ReteVisitor.h"
#include "WorkingMemory.h"

class Tuple;
class Fact;

class TupleFactList
{
public:
	class Iterator
	{
	public:
		Iterator(TupleFactList *list) : list(list)
		{
			fact = list->facts.begin();
			tuple = list->tuples.begin();
		}

		std::vector<Fact *>::iterator fact;
		std::vector<Tuple *>::iterator tuple;
		bool next();
	private:
		TupleFactList *list;
	};

	friend bool TupleFactList::Iterator::next();

public:

	size_t count;

	void add(Fact *fact, Tuple *tuple);
	Iterator iterator();
private:
	std::vector<Fact *> facts;
	std::vector<Tuple *> tuples;
};

class BetaMemoryNode : public ObjectSink<TupleFactList *>, public ObjectSource<std::vector<Tuple *>>, public ReteVisitableImpl<BetaMemoryNode>
{
public:
	std::vector<ObjectSink<std::vector<Tuple *>> *> sinks;

	void propagate_assert(TupleFactList *object, WorkingMemory *memory) override;
	void propagate_update(TupleFactList *object, WorkingMemory *memory) override;
	void propagate_retract(TupleFactList *object, WorkingMemory *memory) override;

	std::vector<Tuple *> get_source(WorkingMemory *memory) override;
	void attach(ObjectSink<std::vector<Tuple *>> *sink) override;
private:
	void propagate_assert_internal(std::vector<Tuple *> object, WorkingMemory *memory, DualMemory<Tuple *, Fact *> *tuple_memory);
	void propagate_update_internal(std::vector<Tuple *> object, WorkingMemory *memory, DualMemory<Tuple *, Fact *> *tuple_memory);
	void propagate_retract_internal(std::vector<Tuple *> object, WorkingMemory *memory, DualMemory<Tuple *, Fact *> *tuple_memory);
};

#endif //_BETAMEMORYNODE_H_
