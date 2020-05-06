#ifndef TILE_H_
#define TILE_H_

#include <cstdint>
#include <string>
#include "Texture.h"
#include "Movable.h"
#include "Renderable.h"
#include "Mesh.h"


namespace Map
{
    class Loader;

    class Tile : public Movable, public Renderable
    {
    public:
        uint16_t zoom;
        int latitude;
        int longitude;
        Texture *texture;
        Mesh *mesh;

        Tile(uint16_t zoom, int latitude, int longitude, Texture *texture);

        virtual ~Tile();

        Tile *get(Loader &loader, int dx, int dy);

        Tile *get_east(Loader &loader);

        Tile *get_north(Loader &loader);

        Tile *get_south(Loader &loader);

        Tile *get_west(Loader &loader);

        Tile *get_parent(Loader &loader);

        Tile *get_parent(Loader &loader, float minUV[2], float maxUV[2]) const;

        bool valid() const;

        std::string get_filename(bool tms = true, bool zxy = true, const std::string &ext = ".png") const;

        void render(WorldMatrix&) override;
    };
}

#endif
