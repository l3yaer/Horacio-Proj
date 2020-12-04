#ifndef _VECTORACTOR_H_
#define _VECTORACTOR_H_
#include <Area.h>
#include "SceneNode.h"
#include "RegularPolygon.h"
#include "NodeVisitor.h"

class VectorArea : public Area, public VisitableNodeImpl<VectorArea> {
private:
	Mesh<Shape::RegularPolygonData> *mesh;

public:
	Coordinate coordinate;

	VectorArea(const std::string &name, Coordinate coordinate, Scale scale, int sides, Color color, float opacity);

	void update(float msec) override;

	void render() override;

	Color color;

	float opacity;
};

#endif //_VECTORACTOR_H_
