#include "NodeRendererVisitor.h"
#include "VectorArea.h"
#include "GuiActor.h"
#include "Renderer.h"
#include "Program.h"
#include "Tile.h"
#include "GuiMap.h"
#include <LogManager.h>

NodeRendererVisitor::NodeRendererVisitor(Renderer *renderer) : renderer(renderer)
{}

void NodeRendererVisitor::visit(Actor &node)
{}

void NodeRendererVisitor::visit(Area &node)
{}

void NodeRendererVisitor::visit(GuiActor &node)
{
	renderer->setup(Renderer::Programs::ACTOR);
	renderer->draw_node(node);
}

void NodeRendererVisitor::visit(VectorArea &node)
{
	renderer->setup(Renderer::Programs::VECTOR);
	renderer->get_current_program()->set_vector4({node.color, node.opacity}, "color");
	renderer->draw_node(node);
}

void NodeRendererVisitor::visit(SceneNode &node)
{
	renderer->draw_node(node);
}

void NodeRendererVisitor::visit(Tile &node)
{
	renderer->setup(Renderer::Programs::TILE);
	renderer->draw_node(node);
}

void NodeRendererVisitor::visit(Map &node)
{
	renderer->draw_node(node);
	for (auto *actor : node.actors)
		dynamic_cast<VisitableNode*>(actor)->accept(*this);

	for (auto *area : node.areas)
		dynamic_cast<VisitableNode*>(area)->accept(*this);
}

void NodeRendererVisitor::visit(GuiMap &node)
{
	renderer->draw_node(node);
	for (auto *tile : node.tiles)
		dynamic_cast<VisitableNode*>(tile)->accept(*this);

	for (auto *actor : node.actors)
		dynamic_cast<VisitableNode*>(actor)->accept(*this);

	for (auto *area : node.areas)
		dynamic_cast<VisitableNode*>(area)->accept(*this);
}
