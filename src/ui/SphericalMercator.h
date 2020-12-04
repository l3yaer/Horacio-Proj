#ifndef _SPHERICALMERCATOR_H_
#define _SPHERICALMERCATOR_H_

#include <types.h>

namespace SphericalMercator
{
	Coordinate project(const Coordinate &coordinate);
	Coordinate unproject(const Coordinate &point);
	float scale_zoom(float zoom);
	Coordinate transform(const Coordinate &point, float zoom);
	Coordinate untransform(const Coordinate &point, float zoom);
	Bounds projection_bounds(int zoom);
	Coordinate point_to_coordinate(const Coordinate &point, float zoom);
	Coordinate coordinate_to_point(const Coordinate &coordinate, float zoom);

} // namespace SphericalMercator

#endif
