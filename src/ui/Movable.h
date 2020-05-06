#ifndef MOVABLE_H_
#define MOVABLE_H_

#include <cstdint>
#include <string>
#include <glm/glm.hpp>


typedef glm::vec3 Position ;
typedef glm::vec3 Scale;
typedef glm::vec3 Rotation;

typedef glm::mat4 AffineMatrix;

class Movable
{

public:
    Position position;
    Scale scale;
    Rotation rotation;

    virtual AffineMatrix getMatrix() const;
};



#endif //MOVABLE_H_
