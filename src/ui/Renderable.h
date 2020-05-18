#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

#include "Program.h"
#include "constants.h"

class Renderable
{
 public:
  Program *program = nullptr;

  virtual void render () = 0;
};

#endif //_RENDERABLE_H_
