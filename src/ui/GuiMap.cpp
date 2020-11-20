#include <iostream>
#include <iomanip>
#include <algorithm>
#include <Actor.h>
#include <LogManager.h>
#include "GuiMap.h"
#include "constants.h"
#include "Tile.h"
#include "MapManager.h"
#include "SphericalMercator.h"
#include "World.h"
#include "Layer.h"

double upper_y_limit = 0, lower_y_limit = 0;

GuiMap::GuiMap() : tile_layer(new Layer()), Map()
{
	add_child(tile_layer);
}

GuiMap::~GuiMap()
{
	delete tile_layer;
	Map::~Map();
}

void GuiMap::go_to(Position position)
{
	Map::go_to(position);
	zoom = floor(center.z);
	origin = get_origin({center.x, center.y});
	Bounds pixel_bounds = tile_pixel_bounds();
	Bounds bounds = pixels_to_tile(pixel_bounds);

	std::vector<Position> coordinates;
	for (int j = bounds.first.y; j <= bounds.second.y; j++) {
		for (int i = bounds.first.x; i <= bounds.second.x; i++) {
			coordinates.emplace_back(i, j, zoom);
		}
	}

	add_tiles(coordinates, bounds.second.y + bounds.first.y);
}

void GuiMap::update(float msec)
{
	Map::update(msec);

	Coordinate position_difference = origin - get_origin({current.x, current.y});
	position = { position_difference, 0.0 };

	//if (fabs(position_difference.x) > TILE_SIZE || fabs(position_difference.y) > TILE_SIZE)
	//reset_map(World::instance().get_position());
}

Coordinate GuiMap::get_origin(const Coordinate &coordinate) const
{
	return SphericalMercator::coordinate_to_point(coordinate, zoom) - HALF_MAP_SIZE;
}

void GuiMap::render()
{
	tile_layer->render();
	Map::render();
}

Bounds GuiMap::tile_pixel_bounds()
{
	Coordinate origin = SphericalMercator::coordinate_to_point(center, zoom);
	return { origin - HALF_MAP_SIZE, origin + HALF_MAP_SIZE };
}

Bounds GuiMap::pixels_to_tile(const Bounds &pixels)
{
	Coordinate lowerBound = { floor(pixels.first.x / TILE_SIZE), floor(pixels.first.y / TILE_SIZE) };
	Coordinate upperBound = { ceil(pixels.second.x / TILE_SIZE) - 1, ceil(pixels.second.y / TILE_SIZE) - 1};
	return { lowerBound, upperBound };
}

void GuiMap::add_tiles(std::vector<Position> &coordinates, double y_sum)
{
	tile_layer->clear_children();
	tiles.clear();
	for (auto &position : coordinates) {
		Tile *t = MapManager::instance().get_tile(position.z, position.x, position.y);
		Coordinate coordinate = Coordinate(position.x, position.y) * TILE_SIZE - origin + Coordinate(TILE_SIZE/2.0);
		Position tile_position = { coordinate.x, MAP_HEIGHT - coordinate.y, -99.0f };
		t->position = tile_position;
		t->scale = { TILE_SIZE, TILE_SIZE, 1.0f };
		tiles.emplace_back(t);
		tile_layer->add_child(t);
	}
}


void GuiMap::spawn_actor(Actor *actor)
{
	Coordinate new_pos = SphericalMercator::coordinate_to_point({actor->position.x, actor->position.y}, zoom) - origin;
	actor->position.x = new_pos.x;
	actor->position.y = MAP_HEIGHT - new_pos.y;
	Map::spawn_actor(actor);
}

int GuiMap::get_zoom() const
{
	return zoom;
}

void GuiMap::set_zoom(int zoom)
{
	go_to({current.x, current.y, zoom});
}
