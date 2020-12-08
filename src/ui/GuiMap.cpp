#include <iostream>
#include <iomanip>
#include <algorithm>
#include <Actor.h>
#include <Area.h>
#include <LogManager.h>
#include <Layer.h>
#include "GuiMap.h"
#include "constants.h"
#include "Tile.h"
#include "MapManager.h"
#include "SphericalMercator.h"
#include "World.h"
#include "TileFactory.h"
#include "NodeCoordinateAdapterVisitor.h"

GuiMap::GuiMap(TileFactory *tile_factory) : tile_factory(tile_factory), Map()
{
	add_child(get_layer("tile"));
	get_layer("tile")->position.z = -99.f;
	get_layer("actor")->position.z = -1.f;
	get_layer("area")->position.z = -50.f;
	sort_layers();
}

GuiMap::~GuiMap()
{
}

void GuiMap::go_to(Position position)
{
	Map::go_to(position);
	zoom = floor(center.z);
	origin = get_origin({ center.x, center.y });
	Bounds pixel_bounds = tile_pixel_bounds();
	Bounds bounds = pixels_to_tile(pixel_bounds);

	get_layer("tile")->clear_children();
	tiles.clear();
	for (int j = bounds.first.y; j <= bounds.second.y; j++)
		for (int i = bounds.first.x; i <= bounds.second.x; i++)
			add_tile({ i, j, zoom }, bounds.second.y + bounds.first.y);
}

void GuiMap::update(float msec)
{
	Map::update(msec);

	Coordinate position_difference = origin - get_origin({ current.x, current.y });
	position = { position_difference, 0.0 };

	if (fabs(position_difference.x) > MAP_WIDTH || fabs(position_difference.y) > MAP_HEIGHT)
		go_to(current);

	for (auto *tile : tiles)
		tile_factory->open_image(tile);
}

Coordinate GuiMap::get_origin(const Coordinate &coordinate) const
{
	return SphericalMercator::coordinate_to_point(coordinate, zoom) - HALF_MAP_SIZE;
}

void GuiMap::render()
{
}

Bounds GuiMap::tile_pixel_bounds()
{
	Coordinate origin = SphericalMercator::coordinate_to_point(center, zoom);
	return { origin - HALF_MAP_SIZE, origin + HALF_MAP_SIZE };
}

Bounds GuiMap::pixels_to_tile(const Bounds &pixels)
{
	Coordinate lowerBound = { floor(pixels.first.x / TILE_SIZE), floor(pixels.first.y / TILE_SIZE) };
	Coordinate upperBound = { ceil(pixels.second.x / TILE_SIZE) - 1, ceil(pixels.second.y / TILE_SIZE) - 1 };
	return { lowerBound, upperBound };
}

void GuiMap::add_tile(const Position &coordinate, double y_sum)
{
	NodeCoordinateAdapterVisitor visitor(this);
	Tile *t = tile_factory->get_tile(coordinate.z, coordinate.x, coordinate.y);
	dynamic_cast<VisitableNode *>(t)->accept(visitor);
	tiles.emplace_back(t);
	get_layer("tile")->add_child(t);
}

void GuiMap::spawn(Actor *actor)
{
	NodeCoordinateAdapterVisitor visitor(this);
	dynamic_cast<VisitableNode *>(actor)->accept(visitor);
	Map::spawn(actor);
}

void GuiMap::spawn(Area *area)
{
	NodeCoordinateAdapterVisitor visitor(this);
	dynamic_cast<VisitableNode *>(area)->accept(visitor);
	Map::spawn(area);
}

int GuiMap::get_zoom() const
{
	return zoom;
}

void GuiMap::set_zoom(int zoom)
{
	NodeCoordinateAdapterVisitor visitor(this);
	go_to({ current.x, current.y, zoom });
	for (auto *actor : actors)
		dynamic_cast<VisitableNode *>(actor)->accept(visitor);

	for (auto *area : areas)
		dynamic_cast<VisitableNode *>(area)->accept(visitor);
}
