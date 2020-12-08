#include "Map.h"
#include <algorithm>
#include "World.h"
#include "Layer.h"
#include "Actor.h"
#include "Area.h"

struct LayerPairNameComparator {
	explicit LayerPairNameComparator(const std::string &name) : name(name)
	{
	}

	inline bool operator()(const Map::LayerPair &pair)
	{
		return pair.first == name;
	}

private:
	std::string name;
};

struct LayerPairZPosComparator {
	inline bool operator()(const Map::LayerPair &rhs, const Map::LayerPair &lhs)
	{
		return lhs.second->position.z > rhs.second->position.z;
	}
};

Map::Map() : SceneNode()
{
	add_child(get_layer("actor"));
	add_child(get_layer("area"));
}

Map::~Map()
{
	for (auto layer_pair : layers)
		delete layer_pair.second;
	for (auto actor : actors)
		delete actor;
	for (auto area : areas)
		delete area;
}

void Map::go_to(Position position)
{
	center = position;
	current = center;
}

void Map::spawn(Actor *actor)
{
	get_layer("actor")->add_child(actor);
	actors.emplace_back(actor);
}

void Map::spawn(Area *area)
{
	get_layer("area")->add_child(area);
	areas.emplace_back(area);
}

void Map::update(float msec)
{
	current = { World::instance().get_position(), center.z };

	SceneNode::update(msec);
}

void Map::render()
{
}

std::vector<Map::LayerPair> Map::get_layers() const
{
	return layers;
}

Layer *Map::get_layer(const std::string &name)
{
	std::vector<LayerPair>::iterator layer = std::find_if(layers.begin(), layers.end(), LayerPairNameComparator(name));
	if (layer != layers.end())
		return (*layer).second;

	LayerPair pair(name, new Layer());
	layers.push_back(pair);
	sort_layers();
	return pair.second;
}

void Map::sort_layers()
{
	std::sort(layers.begin(), layers.end(), LayerPairZPosComparator());
}
