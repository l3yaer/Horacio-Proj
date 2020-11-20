#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include "SceneNode.h"
#include "types.h"

class Layer;

class Actor;

class Map : public SceneNode
{
protected:
	Position center;
	Position current;

	Layer *actor_layer;
public:
	Map();
	virtual ~Map();

	virtual void go_to(Position coordinate);
	virtual void spawn_actor(Actor *actor);

	virtual void update(float msec) override;
	virtual void render() override;

	std::vector<Actor *> actors;
};

#endif //_MAP_H_
