#ifndef _MOVABLE_H_
#define _MOVABLE_H_

#include <cstdint>
#include <string>
#include <glm/glm.hpp>

typedef glm::vec3 Position;
typedef glm::vec3 Scale;
typedef glm::vec3 Rotation;

typedef glm::mat4 AffineMatrix;

class Movable
{

 public:
  Position position = Position (0.0f);
  Scale scale = Scale (1.0f);
  Rotation rotation = Rotation (0.0f);

  virtual AffineMatrix matrix () const;
};

#endif //_MOVABLE_H_
