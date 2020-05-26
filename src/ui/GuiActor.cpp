#include "GuiActor.h"
#include <World.h>
#include "TextureManager.h"
#include "ProgramManager.h"
#include "Square.h"
#include "MapCoordinatesAdapter.h"

Mesh *m;

GuiActor::GuiActor (const std::string &name, Position position, Scale scale) : Actor (name, position, scale)
{
	if (!m) m = new Shape::Square (1.0f);
	texture = TextureManager::instance ().create ("circle", "data/circle.png");
	program = ProgramManager::instance ().create ("actor");
	mesh = m;
}

void GuiActor::render ()
{
	if (texture && texture->is_ready ()) texture->use ();
	program->use (matrix (), World::instance ().get_matrix (), World::instance ().get_view ());
	mesh->draw ();
}

void GuiActor::set_position (const Position &position, const Coordinate &correction, const Position &map_center)
{
	Movable::position = position;
	map_position = Position (
			MapCoordinatesAdapter::adapt_object_location ({position.x, position.y}, correction, map_center),
			position.z);
}

AffineMatrix GuiActor::matrix () const
{
	return calculate_matrix (map_position, scale, rotation);
}
