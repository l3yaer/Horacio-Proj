#ifndef TILEFACTORY_H_
#define TILEFACTORY_H_

#include <string>
#include <map>
#include <cstdint>
#include "Square.h"
#include "Program.h"


namespace Map
{

    class Loader;

    class Tile;

    class TileFactory
    {
    private:
        std::map<std::string, Tile *> tiles;

        Shape::Square *square;

        Program *program;

        TileFactory(const TileFactory &) {}

        ~TileFactory();

        static std::string tile_id(uint16_t zoom, uint64_t x, uint64_t y);

    public:

        TileFactory();

        Tile *get_tile(Loader &loader, uint16_t zoom, int x, int y);

        Tile *get_tile_at(Loader &loader, uint16_t zoom, double x, double y);

    };
}

#endif //TILEFACTORY_H_
