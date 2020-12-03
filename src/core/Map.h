#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include "SceneNode.h"
#include "types.h"
#include "Visitor.h"

class Layer;

class Actor;

class Area;

class Map : public SceneNode, public VisitableImpl<Map, Map, SceneNode>
{
protected:
	Position center;
	Position current;

	Layer *actor_layer;
	Layer *area_layer;
public:
	Map();
	virtual ~Map();

	virtual void go_to(Position coordinate);
	virtual void spawn(Actor *actor);
	virtual void spawn(Area *actor);

	virtual void update(float msec) override;
	virtual void render() override;

	std::vector<Actor *> actors;
	std::vector<Area *> areas;
};

#endif //_MAP_H_
