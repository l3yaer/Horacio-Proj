#include "AlphaNode.h"

void AlphaNode::add(const MemoryElement &wme)
{
	output.push_back(wme);
}

const MemoryElementVector &AlphaNode::get_output()
{
	std::cout << "Alpha output" << std::endl;
	return output;
}

void AlphaNode::clear()
{
	output.clear();
}
