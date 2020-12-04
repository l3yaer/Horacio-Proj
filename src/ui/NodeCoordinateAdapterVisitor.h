#ifndef _NODECOORDINATEADAPTERVISITOR_H_
#define _NODECOORDINATEADAPTERVISITOR_H_

#include <types.h>
#include "NodeVisitor.h"

class GuiMap;

class NodeCoordinateAdapterVisitor : public VisitorNode {
public:
	NodeCoordinateAdapterVisitor(GuiMap *map);

	virtual void visit(Actor &node) override;
	virtual void visit(Area &node) override;
	virtual void visit(GuiActor &node) override;
	virtual void visit(VectorArea &node) override;
	virtual void visit(SceneNode &node) override;
	virtual void visit(Tile &node) override;
	virtual void visit(GuiMap &node) override;
	virtual void visit(Map &node) override;
private:
	GuiMap *map;

	Position correct_position(const Coordinate coordinate);
};

#endif // _NODECOORDINATEADAPTERVISITOR_H_
