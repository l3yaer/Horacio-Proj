#include "Layer.h"
//#include "constants.h"

#include <iostream>

void Map::Layer::update(float msec)
{
/*	if (fabs(position.x) > TILE_SIZE)
		position.x = position.x - (position.x < 0 ? -TILE_SIZE : TILE_SIZE);
	if (fabs(position.y) > TILE_SIZE)
		position.y = position.y - (position.y < 0 ? -TILE_SIZE : TILE_SIZE);
*/
	SceneNode::update(msec);
}

void Map::Layer::render()
{
}

void Map::Layer::clear_children()
{
	this->children.clear();
}
