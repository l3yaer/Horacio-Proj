#include "AlphaMemory.h"
#include <algorithm>

void AlphaMemory::add(Fact* item)
{
	facts.push_back(item);
}

void AlphaMemory::remove(Fact* item)
{
	facts.erase(std::remove(facts.begin(), facts.end(), item), facts.end());
}

bool AlphaMemory::contains(Fact* item)
{
	return std::find(facts.begin(), facts.end(), item) != facts.end();
}

std::vector<Fact *> AlphaMemory::data() const
{
	return facts;
}
