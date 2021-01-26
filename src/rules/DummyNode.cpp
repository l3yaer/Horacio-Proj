#include "DummyNode.h"

DummyNode::DummyNode()
	: ReteNode(true)
{
	output.push_back({});
}

void DummyNode::clear()
{
}

const TokenVector &DummyNode::get_output()
{
	return output;
}
