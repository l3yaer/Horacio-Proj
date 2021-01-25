#include "BetaMemoryNode.cpp"
#include "Fact.h"
#include "Tuple.h"

void TupleFactList::add(Fact *fact, Tuple *tuple)
{
	facts.push_back(fact);
	tuples.push_back(tuple);
	++count;
}

TupleFactList::Iterator TupleFactList::iterator()
{
	return TupleFactList::Iterator(this);
}

bool TupleFactList::Iterator::next()
{
	++fact;
	++tuple;
	return fact != list->facts.end() && tuple != list->tuples.end();
}
