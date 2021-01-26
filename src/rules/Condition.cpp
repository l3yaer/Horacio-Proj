#include "Condition.h"
#include <iostream>

bool Condition::test_constant(Triple::Field field_name) const
{
	return !Triple::is_param(get(field_name));
}

Condition Condition::index() const
{
	Condition ret = *this;
	if(!ret.test_constant(ID))
		ret.fields.at(0) = "*";
	if(!ret.test_constant(ATTR))
		ret.fields.at(1) = "*";
	if(!ret.test_constant(VALUE))
		ret.fields.at(2) = "*";
	return ret;
}

const Condition::Type &Condition::get_type() const
{
	return type;
}

bool Condition::operator==(const Condition &rhs) const
{
	return fields.at(0) == rhs.fields.at(0) &&
		fields.at(1) == rhs.fields.at(1) &&
		fields.at(2) == rhs.fields.at(2) &&
		type == rhs.type;
}

void Condition::print() const
{
	std::cout << fields.at(0) << ","
		<< (type == NEGATIVE ? "~" : "")
		<< fields.at(1)
		<< "," << fields.at(2) << std::endl;
}
