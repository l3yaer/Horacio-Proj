#include "Actor.h"
#include <algorithm>
#include "LogManager.h"
#include "Action.h"

Actor::Actor(const std::string &name, Coordinate coordinate, Scale scale) :
	SceneNode(), name(name), coordinate(coordinate)
{
	this->scale = scale;
	this->position = Position(coordinate, 0);
}

void Actor::update(float msec)
{
	SceneNode::update(msec);
	for(auto action : actions)
		action->update(msec);

	std::vector<Action *>::iterator finished = std::partition(actions.begin(), actions.end(), Action::did_finish);

	for(std::vector<Action *>::iterator it = actions.begin(); it != finished; ++it)
	{
		delete (*it);
	}

	actions.erase(actions.begin(), finished);
}

void Actor::add_action(Action *action)
{
	actions.push_back(action);
}
