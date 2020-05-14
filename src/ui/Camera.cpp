#include <glm/ext/matrix_transform.hpp>
#include "Camera.h"

Camera::Camera (const Position &position, const Front &front, const Up &up)
	: position (position), front (front), up (up)
{}

void Camera::apply_movement (const Position &direction)
{
  if (direction.z) position += speed * front * (direction.z > 0 ? 1.0f : -1.0f);
  if (direction.x) position += speed * glm::normalize (glm::cross (front, up)) * (direction.x > 0 ? 1.0f : -1.0f);
  if (direction.y) position += speed * up * (direction.y > 0 ? 1.0f : -1.0f);
  dirty = true;
}

void Camera::move_to (const Position &position)
{
  this->position = position;
  dirty = true;
}

AffineMatrix Camera::matrix ()
{
  if (dirty)
	{
	  affine_matrix = glm::lookAt (position, position + front, up);
	  dirty = false;
	}

  return affine_matrix;
}
