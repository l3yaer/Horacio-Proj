#include "BetaMemory.h"
#include <algorithm>
#include "Fact.h"
#include "Tuple.h"

BetaMemory::BetaMemory() : null_fact(new Fact())
{}

BetaMemory::~BetaMemory()
{
	delete null_fact;
}

std::vector<Tuple *> BetaMemory::data() const
{
	return tuples;
}

void BetaMemory::add(Tuple* item)
{
	tuples.push_back(item);

	if(item->left_tuple == nullptr)
		return;

	std::unordered_map<Fact *, Tuple *> sub_map = parent_child_map[item->left_tuple];
	Fact *fact = item->right_fact == nullptr ? null_fact : item->right_fact;
	sub_map[fact] = item;
	parent_child_map[item->left_tuple] = sub_map;
}

void BetaMemory::remove(Tuple* item)
{
	tuples.erase(std::remove(tuples.begin(), tuples.end(), item), tuples.end());

	if(item->left_tuple == nullptr)
		return;

	std::unordered_map<Fact *, Tuple *> sub_map = parent_child_map[item->left_tuple];
	Fact *fact = item->right_fact == nullptr ? null_fact : item->right_fact;
	sub_map.erase(fact);
	parent_child_map[item->left_tuple] = sub_map;
}

bool BetaMemory::contains(Tuple* item)
{
	return std::find(tuples.begin(), tuples.end(), item) != tuples.end();
}

Tuple *BetaMemory::find(Tuple *left, Fact *right)
{
	std::unordered_map<Fact *, Tuple *> sub_map = parent_child_map[left];

	if(sub_map.empty())
		return nullptr;

	return sub_map[right];
}
