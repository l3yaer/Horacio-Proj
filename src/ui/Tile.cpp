#include <sstream>
#include <iostream>
#include "Tile.h"
#include "Texture.h"

Tile::Tile(uint16_t zoom, int x, int y, Texture *texture) : SceneNode(), zoom(zoom), x(x), y(y), texture(texture), mesh(nullptr)
{
}

std::string Tile::get_filename(const std::string &ext) const
{
	std::stringstream filename;
	filename << zoom << "/" << x << '/' << y << ext;
	return filename.str();
}

Tile::~Tile()
{
	delete texture;
}

Coordinate Tile::coordinate()
{
	return { x, y };
}

void Tile::update(float msec)
{
	SceneNode::update(msec);
}

void Tile::render()
{
	if (texture && texture->is_ready())
		texture->use();
	mesh->draw();
}
