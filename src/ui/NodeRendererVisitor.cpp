#include "NodeRendererVisitor.h"
#include "VectorArea.h"
#include "GuiActor.h"
#include "Renderer.h"
#include "Program.h"
#include "Tile.h"
#include "GuiMap.h"
#include <Layer.h>
#include <LogManager.h>

NodeRendererVisitor::NodeRendererVisitor(Renderer *renderer) : renderer(renderer)
{
}

void NodeRendererVisitor::visit(Actor &node)
{
}

void NodeRendererVisitor::visit(Area &node)
{
}

void NodeRendererVisitor::visit(Layer &node)
{
	renderer->draw_node(node);
	for (auto child : node.get_children()) {
		VisitableNode *visitable = dynamic_cast<VisitableNode *>(child);
		if (visitable != nullptr)
			visitable->accept(*this);
		else
			child->accept(*this);
	}
}

void NodeRendererVisitor::visit(GuiActor &node)
{
	renderer->setup(Renderer::Programs::ACTOR);
	renderer->draw_node(node);
}

void NodeRendererVisitor::visit(VectorArea &node)
{
	renderer->setup(Renderer::Programs::VECTOR);
	renderer->get_current_program()->set_vector4({ node.color, node.opacity }, "color");
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
	for (auto layer : node.get_layers())
		dynamic_cast<VisitableLayerNode *>(layer.second)->accept(*this);
}

void NodeRendererVisitor::visit(GuiMap &node)
{
	renderer->draw_node(node);
	for (auto layer : node.get_layers())
		dynamic_cast<VisitableLayerNode *>(layer.second)->accept(*this);
}
