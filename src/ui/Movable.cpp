#include "Movable.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

AffineMatrix Movable::getMatrix() const
{
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, position);
    trans = glm::scale(trans, scale);
    return trans;
}
