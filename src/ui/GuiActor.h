#ifndef _GUIACTOR_H_
#define _GUIACTOR_H_
#include <Actor.h>
#include "SceneNode.h"
#include "Texture.h"
#include "Mesh.h"

class GuiActor : public Actor {
private:
	Texture *texture;
	Mesh *mesh;

public:
	GuiActor(const std::string &name, Position position, Scale scale);

	void update(float msec) override;

	void render() override;};

#endif //_GUIACTOR_H_
