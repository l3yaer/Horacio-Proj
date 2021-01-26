#ifndef _CONDITION_H_
#define _CONDITION_H_

#include <iostream>
#include "Triple.h"

class Condition : public Triple
{
public:
	enum Type
	{
		POSITIVE, NEGATIVE
	};

	template<typename Id, typename Attr, typename Value>
	Condition(const Id &id, const Attr &attr, const Value &value, Type type = POSITIVE)
		: Triple(id, attr, value), type(type)
	{}

	bool test_constant(Triple::Field field_name) const;
	Condition index() const;
	const Type &get_type() const;
	bool operator==(const Condition &rhs) const;
	void print() const;
protected:
	Type type;
};

using ConditionVector = std::vector<Condition>;

namespace std
{
	template<>
	struct hash<Condition>
	{
		size_t operator()(const Condition &c) const
		{
			size_t ret = 2166136261;
			ret = (ret * 16777619) ^ hash<string>()(c.get(Triple::Field::ID));
			ret = (ret * 16777619) ^ hash<string>()(c.get(Triple::Field::ATTR));
			ret = (ret * 16777619) ^ hash<string>()(c.get(Triple::Field::VALUE));
			ret = (ret * 16777619) ^ hash<Condition::Type>()(c.get_type());
			return ret;
		}
	};
}


#endif //_CONDITION_H_
