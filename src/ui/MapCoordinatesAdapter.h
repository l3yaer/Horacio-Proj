#ifndef _MAPCOORDINATESADAPTER_H_
#define _MAPCOORDINATESADAPTER_H_

#include <cmath>
#include <glm/glm.hpp>
#include "constants.h"

typedef glm::vec2 Coordinate;

class MapCoordinatesAdapter
{
 public:

  static double latitude_size (double latitude, int zoom)
  {
	int tile = latitude_to_tile_y (latitude, zoom);
	return (tile_to_latitude (tile, zoom) - tile_to_latitude (tile + 1, zoom)) / 2;
  }

  static double longitude_size (int zoom)
  {
	return 1 / pow (2.0, zoom) * 180.0;
  }

  static int longitude_to_tile_x (double lon, int z)
  {
	return (int)(floor ((lon + 180.0) / 360.0 * (1 << z)));
  }

  static int latitude_to_tile_y (double lat, int z)
  {
	double latitude_radian = lat * M_PI / 180.0;
	return (int)(floor ((1.0 - asinh (tan (latitude_radian)) / M_PI) / 2.0 * (1 << z)));
  }

  static double f_longitude_to_tile_x (double lon, int z)
  {
	return (lon + 180.0) / 360.0 * (1 << z);
  }

  static double f_latitude_to_tile_y (double lat, int z)
  {
	double latitude_radian = lat * M_PI / 180.0;
	return (1.0 - asinh (tan (latitude_radian)) / M_PI) / 2.0 * (1 << z);
  }

  static Coordinate
  calculate_position_correction (Coordinate center_tile_coordinate, int zoom, Coordinate current_position)
  {
	double tile_latitude = tile_to_latitude (center_tile_coordinate.y, zoom) - current_position.y;
	double tile_longitude = tile_to_longitude (center_tile_coordinate.x, zoom) - current_position.x;
	return {
		tile_latitude * HALF_TILE / latitude_size (current_position.y, zoom),
		tile_longitude * HALF_TILE / longitude_size (zoom)
	};
  }

  static Coordinate coord_to_screen (Coordinate coordinate, Coordinate position_correction)
  {
	return {
		TILE_SIZE * coordinate.x + position_correction.x,
		TILE_SIZE * coordinate.y + position_correction.y,
	};
  }

  static Coordinate
  adapt_object_location (Coordinate coordinate, int zoom, Coordinate position_correction, Coordinate center_tile)
  {
	return coord_to_screen (
		{
			(MapCoordinatesAdapter::f_longitude_to_tile_x (coordinate.x, zoom) - center_tile.x),
			(center_tile.y - MapCoordinatesAdapter::f_latitude_to_tile_y (coordinate.y, zoom))
		},
		position_correction
	);
  }

  static double tile_to_longitude (int x, int z)
  {
	return x / (double)(1 << z) * 360.0 - 180;
  }

  static double tile_to_latitude (int y, int z)
  {
	double n = M_PI - 2.0 * M_PI * y / (double)(1 << z);
	return 180.0 / M_PI * atan (0.5 * (exp (n) - exp (-n)));
  }

};

#endif //_MAPCOORDINATESADAPTER_H_
