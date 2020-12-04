#ifndef _ACTORRENDERERVISITOR_H_
#define _ACTORRENDERERVISITOR_H_

#include "NodeVisitor.h"

class Renderer;

class NodeRendererVisitor : public VisitorNode {
public:
	NodeRendererVisitor(Renderer *renderer);

	virtual void visit(Actor &node) override;
	virtual void visit(Area &node) override;
	virtual void visit(GuiActor &node) override;
	virtual void visit(VectorArea &node) override;
	virtual void visit(Layer &node) override;
	virtual void visit(SceneNode &node) override;
	virtual void visit(Tile &node) override;
	virtual void visit(GuiMap &node) override;
	virtual void visit(Map &node) override;

private:
	Renderer *renderer;
};

#endif //_ACTORRENDERERVISITOR_H_
