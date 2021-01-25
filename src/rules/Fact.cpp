#include "Fact.h"
#include <algorithm>

Fact::Fact(Template *templ) : template_class(templ)
{
	for(auto attr : templ->attributes)
		fields[attr] = new VoidValue();
}

Fact::Fact()
{}

Fact::~Fact()
{
	std::unordered_map<std::string, PrimitiveValue *>::iterator it = fields.begin();
    while(it != fields.end())
	{
		delete it->second;
		fields.erase(it);
	}
}

void Fact::set_field(const std::string &name, float value)
{
	if(fields[name] != nullptr)
		delete fields[name];

	fields[name] = new FloatValue(value);
}

void Fact::set_field(const std::string &name, int value)
{
	if(fields[name] != nullptr)
		delete fields[name];

	fields[name] = new IntegerValue(value);
}

void Fact::set_field(const std::string &name, const std::string &value)
{
	if(fields[name] != nullptr)
		delete fields[name];

	fields[name] = new StringValue(value);
}

void Fact::set_field(const std::string &name, const std::vector<PrimitiveValue *> value)
{
	if(fields[name] != nullptr)
		delete fields[name];

	fields[name] = new MultifieldValue(value);
}

bool Fact::operator== (const Fact &o)
{
	std::vector<std::pair<std::string, PrimitiveValue*>> diff;
	std::set_symmetric_difference(fields.begin(), fields.end(),
								  o.fields.begin(), o.fields.end(),
								  std::back_inserter(diff));
	return diff.empty();
}
