#ifndef _ACTORRENDERERVISITOR_H_
#define _ACTORRENDERERVISITOR_H_

#include "NodeVisitor.h"

class Renderer;

class NodeRendererVisitor : public VisitorNode {
public:
	NodeRendererVisitor(Renderer *renderer);

	virtual void visit(Actor &actor) override;
	virtual void visit(Area &actor) override;
	virtual void visit(GuiActor &actor) override;
	virtual void visit(VectorArea &actor) override;
	virtual void visit(SceneNode &actor) override;
	virtual void visit(Tile &actor) override;

private:
	Renderer *renderer;
};

#endif //_ACTORRENDERERVISITOR_H_
