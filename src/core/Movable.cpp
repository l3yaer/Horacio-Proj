#include "Movable.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

AffineMatrix Movable::matrix() const
{
	return calculate_matrix(position, scale, rotation);
}

AffineMatrix Movable::calculate_matrix(const Position &position, const Scale &scale, const Rotation &rotation) const
{
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, position);
	trans = glm::scale(trans, scale);
	if (rotation.x)
		trans = glm::rotate(trans, rotation.x, glm::vec3(1, 0, 0));
	if (rotation.y)
		trans = glm::rotate(trans, rotation.y, glm::vec3(0, 1, 0));
	if (rotation.y)
		trans = glm::rotate(trans, rotation.z, glm::vec3(0, 0, 1));
	return trans;
}
