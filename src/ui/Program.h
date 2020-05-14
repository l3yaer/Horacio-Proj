#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <glm/glm.hpp>
#include <string>

class Program
{
 private:
  unsigned int program_id;

 public:

  Program (const std::string &vertex_shader, const std::string &fragment_shader);

  virtual ~Program ();

  void use (const glm::mat4 &model, const glm::mat4 &projection, const glm::mat4 &view);

};

#endif //_PROGRAM_H_
