#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml.hpp"

class Parser {
public:
	Parser(const std::string path);

	void parse();

private:
	rapidxml::xml_document<> document;
	rapidxml::xml_node<> *root_node;
	std::vector<char> buffer;
};

#endif //_PARSER_H_
