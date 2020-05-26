#ifndef _GUIACTOR_H_
#define _GUIACTOR_H_
#include <Actor.h>
#include "Renderable.h"
#include "Texture.h"
#include "Mesh.h"

class GuiActor : public Actor, public Renderable
{
 private:
	Texture *texture;
	Mesh *mesh;
 public:
	GuiActor(const std::string &name, Position position, Scale scale);

	void render () override;
};

#endif //_GUIACTOR_H_
