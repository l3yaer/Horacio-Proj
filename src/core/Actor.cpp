#include "Actor.h"

Actor::Actor(const std::string &name, Coordinate coordinate, Scale scale) :
	SceneNode(), name(name), coordinate(coordinate)
{
	this->scale = scale;
	this->position = Position(coordinate, 0);
}
