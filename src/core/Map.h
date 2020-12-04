#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include <utility>
#include <string>
#include "SceneNode.h"
#include "types.h"
#include "Visitor.h"

class Layer;

class Actor;

class Area;

class Map : public SceneNode, public VisitableImpl<Map, Map, SceneNode>
{
public:
	typedef std::pair<std::string, Layer*> LayerPair;

	Map();
	virtual ~Map();

	virtual void go_to(Position coordinate);
	virtual void spawn(Actor *actor);
	virtual void spawn(Area *actor);

	virtual void update(float msec) override;
	virtual void render() override;

	virtual std::vector<LayerPair> get_layers() const;

	std::vector<Actor *> actors;
	std::vector<Area *> areas;

protected:
	Position center;
	Position current;

	std::vector<LayerPair> layers;
	Layer *get_layer(const std::string &name);
	void sort_layers();
};

#endif //_MAP_H_
