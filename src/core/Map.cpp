#include "Map.h"
#include "World.h"
#include "Layer.h"
#include "Actor.h"
#include "Area.h"

Map::Map() : actor_layer(new Layer()), area_layer(new Layer()),  SceneNode()
{
	add_child(actor_layer);
	add_child(area_layer);
}

Map::~Map()
{
	delete actor_layer;
	delete area_layer;
}

void Map::go_to(Position position)
{
	center = position;
	current = center;
}

void Map::spawn(Actor *actor)
{
	actor_layer->add_child(actor);
	actors.emplace_back(actor);
}

void Map::spawn(Area *area)
{
	area_layer->add_child(area);
	areas.emplace_back(area);
}


void Map::update(float msec)
{
	current = {World::instance().get_position(), center.z};

	SceneNode::update(msec);
}

void Map::render()
{
	actor_layer->render();
}
