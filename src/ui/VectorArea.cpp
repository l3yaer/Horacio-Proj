#include "VectorArea.h"
#include "constants.h"
#include "MeshManager.h"

VectorArea::VectorArea(const std::string &name, Coordinate coordinate, Scale scale, int sides, Color color,
					   float opacity)
		: Area(name), color(color), opacity(opacity), coordinate(coordinate)
{
	this->scale = scale;
	mesh = MeshManager::instance().create_shape<Shape::RegularPolygonData>("rpoly", { 1.0f, sides });
}

void VectorArea::update(float msec)
{
	Actor::update(msec);
}

void VectorArea::render()
{
	if (position.x + scale.x < 0 || position.x - scale.x > MAP_WIDTH || position.y + scale.y < 0 ||
		position.y - scale.y > MAP_HEIGHT)
		return;

	mesh->draw();
}
