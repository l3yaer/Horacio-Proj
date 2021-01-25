#ifndef _FACT_H_
#define _FACT_H_

#include <string>
#include <unordered_map>
#include <cstring>
#include "Template.h"
#include "Value.h"

class Fact
{
protected:
	std::unordered_map<std::string, PrimitiveValue *> fields;

public:
	Fact(Template *templ);
	Fact();
	~Fact();

	void set_field(const std::string &name, float value);
	void set_field(const std::string &name, int value);
	void set_field(const std::string &name, const std::string &value);
	void set_field(const std::string &name, const std::vector<PrimitiveValue *> value);

	bool operator== (const Fact &o);

	Template *template_class;
};

#endif //_FACT_H_
