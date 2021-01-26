#include "Triple.h"

size_t Triple::get_index(Triple::Field field_name) const
{
	switch(field_name)
	{
	case ID:
		return 0;
	case ATTR:
		return 1;
	case VALUE:
		return 2;
	default:
		return -1;
	}
}

void Triple::set(Triple::Field field_name, const std::string &value)
{
	fields.at(get_index(field_name)) = value;
}

const std::string &Triple::get(Triple::Field field_name) const
{
	return fields.at(get_index(field_name));
}
