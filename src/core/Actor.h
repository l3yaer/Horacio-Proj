#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <string>
#include <vector>
#include "types.h"
#include "SceneNode.h"
#include "Visitor.h"

class Action;

class Actor : public SceneNode, public VisitableImpl<Actor, Actor, SceneNode> {
public:
	Actor(const std::string &name);

	virtual void update(float msec) override;

	void add_action(Action *action);

	std::string name;
protected:
	std::vector<Action*> actions;
};

#endif //_ACTOR_H_
