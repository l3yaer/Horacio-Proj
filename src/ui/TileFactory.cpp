#include "TileFactory.h"
#include <glad/glad.h>
#include <sstream>
#include <cmath>
#include "Tile.h"
#include "Loader.h"
#include "Shaders.h"

Map::TileFactory::TileFactory () : square (new Shape::Square (1.0f)),
								   program (new Program (tile_vertex_shader_source, tile_fragment_shader_source))
{}

Map::TileFactory::~TileFactory ()
{
  tiles.clear ();
}

std::string Map::TileFactory::tile_id (uint16_t zoom, uint64_t x, uint64_t y)
{
  std::stringstream ss;
  ss << zoom << "/" << x << "/" << y;
  return ss.str ();
}

Map::Tile *Map::TileFactory::get_tile (Loader &loader, uint16_t zoom, int x, int y)
{
  auto key = tile_id (zoom, x, y);
  auto i = tiles.find (key);
  if (i != tiles.end ())
	{
	  if (i->second->texture && !i->second->texture->valid ()) loader.open_image (*i->second);
	  return i->second;
	}
  Tile *tile = new Tile (zoom, x, y, nullptr);
  loader.load_image (*tile);
  tile->mesh = square;
  tile->program = program;
  tiles[key] = tile;
  return tile;
}

int long2tilex (double lon, int z)
{
  return (int)(floor ((lon + 180.0) / 360.0 * (1 << z)));
}

int lat2tiley (double lat, int z)
{
  double latrad = lat * M_PI / 180.0;
  return (int)(floor ((1.0 - asinh (tan (latrad)) / M_PI) / 2.0 * (1 << z)));
}

double tilex2long (int x, int z)
{
  return x / (double)(1 << z) * 360.0 - 180;
}

double tiley2lat (int y, int z)
{
  double n = M_PI - 2.0 * M_PI * y / (double)(1 << z);
  return 180.0 / M_PI * atan (0.5 * (exp (n) - exp (-n)));
}

Map::Tile *Map::TileFactory::get_tile_at (Loader &loader, uint16_t zoom, double x, double y)
{
  return get_tile (loader, zoom, lat2tiley (x, zoom), long2tilex (y, zoom));
}
