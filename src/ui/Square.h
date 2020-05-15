#ifndef _SQUARE_H_
#define _SQUARE_H_

#include "Mesh.h"

namespace Shape
{
class Square : public Mesh
{
 public:
  explicit Square (float side_size);

  virtual ~Square ();

  void draw () override;

 private:
  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;
};
}

#endif //_SQUARE_H_
