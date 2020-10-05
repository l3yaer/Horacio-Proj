#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>
#include "types.h"

class Camera {
    private:
	bool dirty = true;
	AffineMatrix affine_matrix = AffineMatrix(1.0f);
	Front front;
	Up up;

    public:
	Speed speed = Speed(0.0f);

	Camera(const Position &position = Position(0.0f),
	       const Front &front = Front(0.0f, 0.0f, -1.0f),
	       const Up &up = Up(0.0f, 1.0f, 0.0f));

	void apply_movement(const Position &direction);

	void move_to(const Position &position);

	AffineMatrix matrix();

	Position position;
};

#endif //_CAMERA_H_
