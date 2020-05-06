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
        std::map<std::pair<Loader *, std::string>, Tile *> tiles;
        static TileFactory *_instance;

        Shape::Square *square;
        Program* program;

        TileFactory();

        TileFactory(const TileFactory &) {}

        ~TileFactory();

        static std::string tile_id(uint16_t zoom, uint64_t x, uint64_t y);

    public:
        static TileFactory *instance();

        Tile *get_tile(Loader &loader, uint16_t zoom, int x, int y);

        Tile *get_tile_at(Loader &loader, uint16_t zoom, double x, double y);

    private:

        class CGuard
        {
        public:
            ~CGuard()
            {
                if (TileFactory::_instance != nullptr)
                {
                    delete TileFactory::_instance;
                    TileFactory::_instance = nullptr;
                }
            }
        };

        friend class CGuard;

    };
}

#endif //TILEFACTORY_H_
