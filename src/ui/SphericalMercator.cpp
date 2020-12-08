#include "SphericalMercator.h"

const int R = 6378137;
const float scale = 0.5f / (M_PI * R);
const glm::vec4 transformation = { scale, 0.5, -scale, 0.5 };
const float bound = R * M_PI;
const Bounds bounds = { { -bound, -bound }, { bound, bound } };

namespace SphericalMercator
{
Coordinate project(const Coordinate &coordinate);
Coordinate unproject(const Coordinate &point);
float scale_zoom(float zoom);
Coordinate transform(const Coordinate &point, float zoom);
Coordinate untransform(const Coordinate &point, float zoom);
Bounds projection_bounds(int zoom);
}; // namespace SphericalMercator

Coordinate SphericalMercator::project(const Coordinate &coordinate)
{
	float d = M_PI / 180.0f, max = 85.0511287798, lat = fmax(fmin(max, coordinate.x), -max), sin = sinf(lat * d),
		  x = R * coordinate.y * d, y = R * log((1 + sin) / (1 - sin)) / 2.0f;

	return { x, y };
}

Coordinate SphericalMercator::unproject(const Coordinate &point)
{
	float d = 180.0f / M_PI;
	return { (2 * atan(exp(point.y / R)) - (M_PI / 2.0)) * d, point.x * d / R };
}

float SphericalMercator::scale_zoom(float zoom)
{
	return 256.0f * pow(2, zoom);
}

Coordinate SphericalMercator::transform(const Coordinate &point, float zoom)
{
	float scale = scale_zoom(zoom);
	return { scale * (transformation.x * point.x + transformation.y),
			 scale * (transformation.z * point.y + transformation.w) };
}

Coordinate SphericalMercator::untransform(const Coordinate &point, float zoom)
{
	float scale = scale_zoom(zoom);
	return { (point.x / scale - transformation.y) / transformation.x,
			 (point.y / scale - transformation.w) / transformation.z };
}

Bounds SphericalMercator::projection_bounds(int zoom)
{
	return { transform(bounds.first, scale_zoom(zoom)), transform(bounds.second, scale_zoom(zoom)) };
}

Coordinate SphericalMercator::point_to_coordinate(const Coordinate &point, float zoom)
{
	Coordinate unstransformed_point = untransform(point, zoom);
	return unproject(unstransformed_point);
}

Coordinate SphericalMercator::coordinate_to_point(const Coordinate &coordinate, float zoom)
{
	Coordinate projected_coord = project(coordinate);
	return transform(projected_coord, zoom);
}
