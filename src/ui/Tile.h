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

        bool valid() const;

        std::string get_filename(const std::string &ext = ".png") const;

        void render(const WorldMatrix &world,const ViewMatrix& view) override;
    };
}

#endif
