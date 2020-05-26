#include "Actor.h"
Actor::Actor (const std::string &name, Position position, Scale scale) : name(name)
{
	this->position = position;
	this->scale = scale;
}
