//
// Created by horacio on 4/30/20.
//

#include <sstream>
#include "Tile.h"
#include "Texture.h"
#include "Renderer.h"
#include <World.h>
#include <iostream>

Map::Tile::Tile(uint16_t zoom, int x, int y, Texture *texture)
	: SceneNode(), zoom(zoom), x(x), y(y), texture(texture)
{
}

bool Map::Tile::valid() const
{
	return x < (uint64_t(1) << zoom) && y < (uint64_t(1) << zoom);
}

std::string Map::Tile::get_filename(const std::string &ext) const
{
	std::stringstream filename;
	filename << zoom << "/" << x << '/' << y << ext;
	return filename.str();
}

Map::Tile::~Tile()
{
	delete texture;
}

Coordinate Map::Tile::coordinate()
{
	return { x, y };
}

void Map::Tile::update(float msec)
{
	SceneNode::update(msec);
}

void Map::Tile::render()
{
	if (texture && texture->is_ready())
		texture->use();
	mesh->draw();
}
