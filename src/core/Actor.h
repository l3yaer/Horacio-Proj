#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <string>
#include "types.h"
#include "SceneNode.h"
#include "Visitor.h"

class Actor : public SceneNode, public VisitableImpl<Actor, Actor, SceneNode> {
public:
	Actor(const std::string &name, Coordinate coordinate, Scale scale);
	std::string name;
	Coordinate coordinate;
};

#endif //_ACTOR_H_
