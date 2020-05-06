#ifndef RENDERABLE_H_
#define RENDERABLE_H_


#include "Program.h"
#include <glm/glm.hpp>

typedef glm::mat4 WorldMatrix ;

class Renderable
{
public:
    Program *program;

    virtual void render(WorldMatrix&) = 0;

};


#endif //RENDERABLE_H_
