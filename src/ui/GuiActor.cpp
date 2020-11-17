#include "GuiActor.h"
#include <World.h>
#include "TextureManager.h"
#include "ProgramManager.h"
#include "Square.h"

Mesh *m;

GuiActor::GuiActor(const std::string &name, Position position, Scale scale) : Actor(name, position, scale)
{
	if (!m)
		m = new Shape::Square(1.0f);
	texture = TextureManager::instance().create("circle", "data/circle.png");
	mesh = m;
}

void GuiActor::update(float msec)
{
	SceneNode::update(msec);
}

void GuiActor::render()
{
	if (texture && texture->is_ready())
		texture->use();
	mesh->draw();
}
