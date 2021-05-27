#include "Parser.h"

Parser::Parser(const std::string path)
{
	std::ifstream file(path);
	buffer = std::vector<char>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	document.parse<0>(&buffer[0]);
	root_node = document.first_node();
}

void Parser::parse()
{
}
