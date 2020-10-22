#include <iostream>
#include <algorithm>
#include "GuiMap.h"
#include "constants.h"
#include "Tile.h"
#include "MapManager.h"
#include "SphericalMercator.h"
#include "World.h"
#include "Layer.h"

double upper_y_limit = 0, lower_y_limit = 0;

GuiMap::GuiMap() : tile_layer(new Map::Layer())
{
	add_child(tile_layer);
}

GuiMap::~GuiMap()
{
	delete tile_layer;
}

Coordinate GuiMap::get_center(const Bounds &bounds) const
{
	return { roundf((bounds.first.x + bounds.second.x) / 2), roundf((bounds.first.y + bounds.second.y) / 2) };
}

void GuiMap::go_to(Coordinate coordinate, int zoom)
{
	this->zoom = zoom;
	reset_map(coordinate);
}

void GuiMap::reset_map(Coordinate coordinate)
{
	center = coordinate;
	origin = get_origin(center);
	Bounds pixel_bounds = tile_pixel_bounds();
	Bounds bounds = pixels_to_tile(pixel_bounds);
	Position center_tile = { get_center(bounds), zoom };

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
	current = get_origin(World::instance().get_position());

	Coordinate position_difference = origin - current;
	position = { position_difference, 0.0 };

	if (fabs(position_difference.x) > TILE_SIZE || fabs(position_difference.y) > TILE_SIZE)
		reset_map(World::instance().get_position());

	SceneNode::update(msec);
}

Coordinate GuiMap::get_origin(const Coordinate &coordinate) const
{
	return SphericalMercator::coordinate_to_point(coordinate, zoom) - Coordinate(FRAME_SIZE / 2.0f);
}

void GuiMap::render()
{
	tile_layer->render();
}

Bounds GuiMap::tile_pixel_bounds()
{
	Coordinate origin = SphericalMercator::coordinate_to_point(center, zoom);
	const Coordinate top_left = { FRAME_SIZE / 2.0f, FRAME_SIZE / 2.0f };
	return { origin - top_left, origin + top_left };
}

Bounds GuiMap::pixels_to_tile(const Bounds &pixels)
{
	Coordinate lowerBound = { floor(pixels.first.x / TILE_SIZE), floor(pixels.first.y / TILE_SIZE) };
	Coordinate upperBound = { ceil(pixels.second.x / TILE_SIZE) - 1, ceil(pixels.second.y / TILE_SIZE) - 1 };
	return { lowerBound, upperBound };
}

void GuiMap::add_tiles(std::vector<Position> &coordinates, double y_sum)
{
	tile_layer->clear_children();
	tiles.clear();
	for (auto &position : coordinates) {
		Map::Tile *t = Map::MapManager::instance().get_tile(position.z, position.x, position.y);
		Coordinate coordinate = Coordinate(position.x, y_sum - position.y) * TILE_SIZE - origin;
		Position tile_position = { coordinate, -99.0f };
		t->position = tile_position;
		t->scale = { TILE_SIZE, TILE_SIZE, 1.0f };
		tiles.emplace_back(t);
		tile_layer->add_child(t);
	}
}
