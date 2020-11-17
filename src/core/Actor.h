#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <string>
#include "types.h"
#include "SceneNode.h"

class Actor : public SceneNode {
public:
	Actor(const std::string &name, Position position, Scale scale);
	std::string name;
};

#endif //_ACTOR_H_
