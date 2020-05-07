#ifndef MAPMANAGER_H_
#define MAPMANAGER_H_

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include "WindowRenderable.h"
#include "Singleton.h"

class Program;

class Camera;

namespace Shape { class Square; }

namespace Map
{
    class Loader;

    class TileFactory;

    class Tile;

    class MapManager : public WindowRenderable<SDL_Event>, public Singleton<MapManager>
    {
    private:
        glm::mat4 world;
        Loader *loader;
        TileFactory *factory;
        Camera *camera;
        bool dirty;

        Tile *get_tile(int zoom, int latitude, int longitude);

        void moveCamera(int input);
    public:
        unsigned int FBO;

        MapManager();

        void render() override;

        void update() override;

        void handle_event(SDL_Event *event) override;

    };
}

#endif //MAPMANAGER_H_
