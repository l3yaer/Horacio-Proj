#ifndef _WORLD_H_
#define _WORLD_H_

#include "Singleton.h"
#include "types.h"

class Camera;

class World : public Singleton<World> {
	WorldMatrix matrix;
	Camera *camera;
	Coordinate position;

public:
	World(Size2D size);

	virtual ~World();

	WorldMatrix get_matrix() const;

	ViewMatrix get_view() const;

	Coordinate get_position() const;

	void move_to(Coordinate position);

	void add_position(Coordinate delta);
};

#endif //_WORLD_H_
