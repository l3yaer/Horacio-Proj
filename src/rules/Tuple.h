#ifndef _TUPLE_H_
#define _TUPLE_H_

#include <unordered_map>
#include <vector>
#include "ReteVisitor.h"

class Fact;

class Tuple
{
public:
	Tuple(long id);
	Tuple(long id, Tuple *left, Fact *right);

	template<typename T>
	T *get_state(ReteVisitable *node)
	{
		return dynamic_cast<T *>(state[node]);
	}


	template<typename T>
	T remove_state(ReteVisitable *node)
	{
		T *value = get_state<T>(node);
		state[node] = nullptr;
		return value;
	}

	long group_id(int level);

	Fact *current();
	bool move_next();
	void reset_current();

	long id;
	int level;
	int count;
	Tuple *left_tuple;
	Fact *right_fact;
	std::unordered_map<ReteVisitable *, void *> state;
	std::vector<Fact *> facts;
	long group;

private:
	Fact *current_fact;
};

#endif //_TUPLE_H_
