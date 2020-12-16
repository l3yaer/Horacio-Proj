#include "AlphaNode.h"

TypeNode::TypeNode(Template *type) : type(type), AlphaNode()
{}

bool TypeNode::is_satisfied(Fact *fact, Memory<Fact *> memory) const
{
	return type->name == fact->template_class->name;
}

void TypeNode::propagate_update(std::vector<Fact*> objects, Memory<Fact*> memory)
{
	std::vector<Fact *> to_update;
	for(auto fact : objects)
		if(is_satisfied(fact, memory))
		   to_update.push_back(fact);

	internal_propagate_update(to_update, memory);
}

void TypeNode::propagate_retract(std::vector<Fact*> objects, Memory<Fact*> memory)
{
	std::vector<Fact *> to_retract;
	for(auto fact : objects)
		if(is_satisfied(fact, memory))
		   to_retract.push_back(fact);

	internal_propagate_retract(to_retract, memory);
}
