#ifndef _MAPCOORDINATESADAPTER_H_
#define _MAPCOORDINATESADAPTER_H_

#include <cmath>
#include <Movable.h>
#include "constants.h"

class MapCoordinatesAdapter
{
 public:
  static Position points_to_coordinates (Position point, int zoom)
  {
	double tile_width = 360.0f / pow (2, zoom);
	return {point.x / TILE_SIZE * tile_width, point.y / TILE_SIZE * tile_width, point.z};
  }

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
