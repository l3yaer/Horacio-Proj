#ifndef _BETAMEMORY_H_
#define _BETAMEMORY_H_

#include <vector>
#include <unordered_map>
#include "WorkingMemory.h"

class Fact;

class Tuple;

class BetaMemory : public DualMemory<Tuple *, Fact *>
{
public:
	BetaMemory();
	~BetaMemory();

	std::vector<Tuple *> data() const override;
	void add(Tuple* item) override;
	void remove(Tuple* item) override;
	bool contains(Tuple* item) override;
	Tuple *find(Tuple *left, Fact *right) override;

	std::vector<Tuple *> tuples;
private:
	std::unordered_map<Tuple *, std::unordered_map<Fact *, Tuple *>> parent_child_map;
	Fact *null_fact;
};

#endif //_BETAMEMORY_H_
