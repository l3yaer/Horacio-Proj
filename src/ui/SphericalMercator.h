#ifndef _SPHERICALMERCATOR_H_
#define _SPHERICALMERCATOR_H_

#include <types.h>

namespace SphericalMercator
{
Coordinate point_to_coordinate(const Coordinate &point, float zoom);
Coordinate coordinate_to_point(const Coordinate &coordinate, float zoom);

} // namespace SphericalMercator

#endif
