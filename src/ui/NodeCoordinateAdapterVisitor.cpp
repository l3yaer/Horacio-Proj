#include "NodeCoordinateAdapterVisitor.h"
#include "SphericalMercator.h"
#include "VectorArea.h"
#include "GuiActor.h"
#include "Renderer.h"
#include "Program.h"
#include "Tile.h"
#include "GuiMap.h"


NodeCoordinateAdapterVisitor::NodeCoordinateAdapterVisitor(GuiMap *map) : map(map)
{}

void NodeCoordinateAdapterVisitor::visit(Actor &node)
{}

void NodeCoordinateAdapterVisitor::visit(Area &node)
{}

void NodeCoordinateAdapterVisitor::visit(Layer &node)
{}

void NodeCoordinateAdapterVisitor::visit(GuiActor &node)
{
	node.position = correct_position(node.coordinate);
}

void NodeCoordinateAdapterVisitor::visit(VectorArea &node)
{
	node.position = correct_position(node.coordinate);
}

void NodeCoordinateAdapterVisitor::visit(SceneNode &node)
{}

void NodeCoordinateAdapterVisitor::visit(Tile &node)
{
	Coordinate coordinate = Coordinate(node.x, node.y) * TILE_SIZE - map->origin + Coordinate(TILE_SIZE/2.0);
	Position tile_position = { coordinate.x, MAP_HEIGHT - coordinate.y, 0};
	node.position = tile_position;
	node.scale = { TILE_SIZE, TILE_SIZE, 1.0f };
}

void NodeCoordinateAdapterVisitor::visit(Map &node)
{}

void NodeCoordinateAdapterVisitor::visit(GuiMap &node)
{}

Position NodeCoordinateAdapterVisitor::correct_position(const Coordinate coordinate)
{
	Coordinate new_pos = SphericalMercator::coordinate_to_point(coordinate, map->get_zoom()) - map->origin;
	return {new_pos.x, MAP_HEIGHT - new_pos.y, 0};
}
