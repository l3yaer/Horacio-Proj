#include "NodeRendererVisitor.h"
#include "VectorArea.h"
#include "GuiActor.h"
#include "Renderer.h"
#include "Program.h"
#include "Tile.h"
#include <LogManager.h>

NodeRendererVisitor::NodeRendererVisitor(Renderer *renderer) : renderer(renderer)
{}

void NodeRendererVisitor::visit(Actor &actor)
{}

void NodeRendererVisitor::visit(Area &actor)
{}

void NodeRendererVisitor::visit(GuiActor &actor)
{
	renderer->draw_node(actor);
}

void NodeRendererVisitor::visit(VectorArea &actor)
{
	renderer->get_current_program()->set_vector4({actor.color, actor.opacity}, "color");
	renderer->draw_node(actor);
}

void NodeRendererVisitor::visit(SceneNode &actor)
{
	renderer->draw_node(actor);
}

void NodeRendererVisitor::visit(Tile &actor)
{
	renderer->draw_node(actor);
}
