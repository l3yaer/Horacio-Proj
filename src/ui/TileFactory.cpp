#include "TileFactory.h"
#include <glad/glad.h>
#include <sstream>
#include <iostream>
#include "Tile.h"
#include "Loader.h"
#include "Shaders.h"
#include "MapCoordinatesAdapter.h"
#include "Square.h"

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
			return i->second;
	Tile *tile = new Tile (zoom, x, y, nullptr);
	loader.load_image (*tile);
	tile->mesh = square;
	tile->program = program;
	tiles[key] = tile;
	return tile;
}

Map::Tile *Map::TileFactory::get_tile_at (Loader &loader, uint16_t zoom, double latitude, double longitude)
{
	int x = MapCoordinatesAdapter::longitude_to_tile_x (longitude, zoom);
	int y = MapCoordinatesAdapter::latitude_to_tile_y (latitude, zoom);
	return get_tile (loader, zoom, x, y);
}
