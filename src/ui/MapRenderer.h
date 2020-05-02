#ifndef MAPRENDERER_H_
#define MAPRENDERER_H_

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include "WindowRenderable.h"

class Program;

namespace Shape { class Square; }

namespace Map
{
    class Loader;

    class MapRenderer : public WindowRenderable<SDL_Event>
    {
    public:
        unsigned int FBO;
        unsigned int TBO;
        unsigned int RBO;

        glm::mat4 world;
        Program *program;
        Loader *loader;
        Shape::Square *square;

        MapRenderer();

        void render() override;

        void update() override;

        void handle_event(SDL_Event *event) override;
    };
}

#endif //MAPRENDERER_H_
