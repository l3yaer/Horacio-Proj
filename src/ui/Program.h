#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <string>
#include "constants.h"
#include <types.h>

class Program
{
 private:
  unsigned int program_id;

 public:

  Program (const std::string &vertex_shader, const std::string &fragment_shader);

  virtual ~Program ();

  void use (const Projection &model, const Projection &projection, const Projection &view);

};

#endif //_PROGRAM_H_
