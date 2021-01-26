#ifndef _TRIPLE_H_
#define _TRIPLE_H_

#include <vector>
#include <string>
#include "StringManip.h"

class Triple
{
public:
	enum Field
	{
		ID, ATTR, VALUE, UNDEFINED
	};

	template<typename Id, typename Attr, typename Value>
	Triple(const Id &id, const Attr &attr, const Value &value)
		: fields({StringManip::to_string(id),
				StringManip::to_string(attr),
				StringManip::to_string(value)})
	{
	}

	static bool is_param(const std::string &string)
	{
		return StringManip::starts_with(string, "?");
	}
	void set(Field field_name, const std::string &value);
	const std::string &get(Field field_name) const;
protected:
	std::vector<std::string> fields;
	size_t get_index(Field field_name) const;
};

#endif //_TRIPLE_H_
