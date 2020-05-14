#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

#include "Program.h"
#include <glm/glm.hpp>

typedef glm::mat4 WorldMatrix;
typedef glm::mat4 ViewMatrix;

class Renderable
{
 public:
  Program *program = nullptr;

  virtual void render (const WorldMatrix &world, const ViewMatrix &view) = 0;
};

#endif //_RENDERABLE_H_
