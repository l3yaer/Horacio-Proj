#ifndef _GUIACTOR_H_
#define _GUIACTOR_H_
#include <Actor.h>
#include "Renderable.h"
#include "Texture.h"
#include "Mesh.h"

class GuiActor : public Actor, public Renderable {
    private:
	Texture *texture;
	Mesh *mesh;
	Position map_position;

    public:
	GuiActor(const std::string &name, Position position, Scale scale);

	void render() override;

	void set_position(const Position &position,
			  const Coordinate &correction,
			  const Position &map_center);

	AffineMatrix matrix() const override;
};

#endif //_GUIACTOR_H_
