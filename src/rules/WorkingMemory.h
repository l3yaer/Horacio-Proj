#ifndef _WORKINGMEMORY_H_
#define _WORKINGMEMORY_H_


template<typename T>
class Memory
{
public:
	virtual std::vector<T> data() const;
	virtual void add(T item);
	virtual void remove(T item);
	virtual bool contains(T item);
};

template<typename T, typename U>
class DualMemory : public Memory<T>
{
public:
	virtual T find(T first, U second);
};

class Fact;
class Tuple;
class AlphaMemoryNode;
class BetaMemoryNode;

class WorkingMemory
{
public:
	virtual Memory<Fact *> *get_memory(AlphaMemoryNode *node);
	virtual DualMemory<Tuple *, Fact *> *get_memory(BetaMemoryNode *node);
	virtual long next_tuple_id();
};

#endif //_WORKINGMEMORY_H_
