#include "GuiActor.h"
#include <World.h>
#include "constants.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "Square.h"

GuiActor::GuiActor(const std::string &name, Coordinate coordinate, Scale scale) : Actor(name), coordinate(coordinate)
{
	this->scale = scale;
	texture = TextureManager::instance().create("circle", "data/circle.png");
	mesh = MeshManager::instance().create_shape<float>("square", 1.0f);
}

void GuiActor::update(float msec)
{
	Actor::update(msec);
}

void GuiActor::render()
{
	if (position.x + scale.x < 0 ||
		position.x - scale.x > MAP_WIDTH ||
		position.y + scale.y < 0 ||
		position.y - scale.y > MAP_HEIGHT)
		return;

	if (texture && texture->is_ready())
		texture->use();
	mesh->draw();
}
