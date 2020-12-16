#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include <string>
#include <vector>

class Template
{
public:
	std::string name;
	std::vector<std::string> attributes;

	Template(const std::string &name,  const std::vector<std::string> &attributes) :
		name(name), attributes(attributes)
	{}
};

#endif //_TEMPLATE_H_
