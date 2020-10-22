#include <iostream>
#include <algorithm>
#include "GuiMap.h"
#include "constants.h"
#include "Tile.h"
#include "MapManager.h"

double upper_y_limit = 0, lower_y_limit = 0;

namespace SphericalMercator
{
const int R = 6378137;
const float scale = 0.5f / (M_PI * R);
const glm::vec4 transformation = { scale, 0.5, -scale, 0.5 };
const float bound = R * M_PI;
const Bounds bounds = { { -bound, -bound }, { bound, bound } };

Coordinate project(const Coordinate &coordinate)
{
	float d = M_PI / 180.0f, max = 85.0511287798, lat = fmax(fmin(max, coordinate.x), -max), sin = sinf(lat * d),
		  x = R * coordinate.y * d, y = R * log((1 + sin) / (1 - sin)) / 2.0f;
	return { x, y };
}

float scale_zoom(float zoom)
{
	return 256.0f * pow(2, zoom);
}

Coordinate transform(const Coordinate &point, float zoom)
{
	return { scale_zoom(zoom) * (transformation.x * point.x + transformation.y),
			 scale_zoom(zoom) * (transformation.z * point.y + transformation.w) };
}

Bounds projection_bounds(int zoom)
{
	return { transform(bounds.first, scale_zoom(zoom)), transform(bounds.second, scale_zoom(zoom)) };
}

} // namespace SphericalMercator

Coordinate get_center(const Bounds &bounds)
{
	return { roundf((bounds.first.x + bounds.second.x) / 2), roundf((bounds.first.y + bounds.second.y) / 2) };
}

void GuiMap::go_to(Coordinate coordinate, int zoom)
{
	this->zoom = zoom;
	center = coordinate;
	reset_map(coordinate);
}

void GuiMap::reset_map(Coordinate coordinate)
{
	origin = pixel_origin(coordinate) - Coordinate(FRAME_SIZE / 2.0f, FRAME_SIZE / 2.0f);
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

Coordinate GuiMap::pixel_origin(Coordinate coordinate)
{
	Coordinate projected_coord = SphericalMercator::project(coordinate);
	return SphericalMercator::transform(projected_coord, zoom);
}

Bounds GuiMap::tile_pixel_bounds()
{
	Coordinate origin = pixel_origin(center);
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
	tiles.clear();
	for (auto &position : coordinates) {
		Map::Tile *t = Map::MapManager::instance().get_tile(position.z, position.x, position.y);
		Coordinate coordinate = Coordinate(position.x, y_sum - position.y) * TILE_SIZE - origin;
		Position tile_position = { coordinate, -99.0f };
		t->position = tile_position;
		t->scale = { TILE_SIZE, TILE_SIZE, 1.0f };
		tiles.emplace_back(t);
	}
}
