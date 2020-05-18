//
// Created by horacio on 4/30/20.
//

#include <sstream>
#include "Tile.h"
#include "Texture.h"
#include <World.h>

Map::Tile::Tile (uint16_t zoom, int x, int y, Texture *texture) : zoom (zoom),
																				 x (x),
																				 y (y),
																				 texture (texture)
{}

bool Map::Tile::valid () const
{
  return x < (uint64_t (1) << zoom) && y < (uint64_t (1) << zoom);
}

std::string Map::Tile::get_filename (const std::string &ext) const
{
  std::stringstream filename;
  filename << zoom << "/" << x << '/' << y << ext;
  return filename.str ();
}

Map::Tile::~Tile ()
{
  delete texture;
}

void Map::Tile::render ()
{
  if (texture) texture->use ();
  program->use (matrix (), World::instance().get_matrix(), World::instance().get_view());
  mesh->draw ();
}
