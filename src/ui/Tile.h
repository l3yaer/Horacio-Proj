#ifndef TILE_H_
#define TILE_H_

#include <cstdint>
#include <string>
#include "Texture.h"

namespace Map
{
    class Loader;

    class Tile
    {
    public:
        uint16_t zoom;
        uint64_t x;
        uint64_t y;

        Texture *texture;

        Tile(uint16_t zoom, uint64_t x, uint64_t y, Texture *texture);

        virtual ~Tile();

        Tile *get(Loader &loader, int64_t dx, int64_t dy);

        Tile *get_east(Loader &loader);

        Tile *get_north(Loader &loader);

        Tile *get_south(Loader &loader);

        Tile *get_west(Loader &loader);

        Tile *get_parent(Loader &loader);

        Tile *get_parent(Loader &loader, float minUV[2], float maxUV[2]) const;

        bool valid() const;

        std::string get_filename(bool tms = true, bool zxy = true, const std::string &ext = ".png") const;
    };
}

#endif
