#include "Map.h"
#include "World.h"
#include "Layer.h"
#include "Actor.h"

Map::Map() : actor_layer(new Layer()), SceneNode()
{
	add_child(actor_layer);
}

Map::~Map()
{
	delete actor_layer;
}

void Map::go_to(Position position)
{
	center = position;
	current = center;
}

void Map::spawn_actor(Actor *actor)
{
	actor_layer->add_child(actor);
	actors.emplace_back(actor);
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
