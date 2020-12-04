#ifndef _GUIACTOR_H_
#define _GUIACTOR_H_
#include <Actor.h>
#include "SceneNode.h"
#include "Texture.h"
#include "Mesh.h"
#include "NodeVisitor.h"

class GuiActor : public Actor, public VisitableNodeImpl<GuiActor> {
private:
	Texture *texture;
	Mesh<float> *mesh;

public:
	Coordinate coordinate;

	GuiActor(const std::string &name, Coordinate coordinate, Scale scale);

	void update(float msec) override;

	void render() override;
};

#endif //_GUIACTOR_H_
