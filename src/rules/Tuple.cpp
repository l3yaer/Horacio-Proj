#include "Tuple.h"
#include "Fact.h"

Tuple::Tuple(long id) : id(id), group(0), count(0), level(0)
{}

Tuple::Tuple(long id, Tuple *left, Fact *right)
	: right_fact(right), left_tuple(left)
{
	count = left->count + (right == nullptr ? 0 : 1);
	level = left->level + 1;
}

long Tuple::group_id(int level)
{
	if(level == this->level - 1)
		return group;

	return left_tuple == nullptr ? 0 : left_tuple->group_id(level);
}

Fact *Tuple::current()
{
	return current_fact;
}

bool Tuple::move_next()
{
	Tuple *tuple = this;
	do {
		current_fact = tuple->right_fact;
		tuple = tuple->left_tuple;
	} while(current_fact == nullptr && tuple != nullptr);

	return current_fact != nullptr;
}

void Tuple::reset_current()
{
	current_fact = nullptr;
}
