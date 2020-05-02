//
// Created by horacio on 4/30/20.
//

#include <sstream>
#include "Tile.h"
#include "TileFactory.h"
#include "Texture.h"

Map::Tile::Tile(uint16_t zoom, uint64_t x, uint64_t y, Texture *texture) : zoom(zoom), x(x), y(y), texture(texture) {}

Map::Tile *Map::Tile::get(Map::Loader &loader, int64_t dx, int64_t dy)
{
    const uint64_t m = uint64_t(1) << zoom;
    if (zoom > 0)
        return TileFactory::instance()->get_tile(loader, zoom, (x + dx) % m, (y + dy) % m);
    else
        return TileFactory::instance()->get_tile(loader, 0, 0, 0);
}

Map::Tile *Map::Tile::get_east(Map::Loader &loader)
{
    return get(loader, -1, 0);
}

Map::Tile *Map::Tile::get_north(Map::Loader &loader)
{
    return get(loader, 0, -1);
}

Map::Tile *Map::Tile::get_south(Map::Loader &loader)
{
    return get(loader, 0, 1);
}

Map::Tile *Map::Tile::get_west(Map::Loader &loader)
{
    return get(loader, 1, 0);
}

Map::Tile *Map::Tile::get_parent(Map::Loader &loader)
{
    if (zoom > 0)
        return TileFactory::instance()->get_tile(loader, zoom - 1, x >> 1, y >> 1);
    return nullptr;
}

Map::Tile *Map::Tile::get_parent(Map::Loader &loader, float *minUV, float *maxUV) const
{
    if (zoom > 0)
    {
        minUV[0] *= 0.5;
        maxUV[0] *= 0.5;
        minUV[0] += (x & 1) ? 0.5 : 0.0;
        maxUV[0] += (x & 1) ? 0.5 : 0.0;

        minUV[1] *= 0.5;
        maxUV[1] *= 0.5;
        minUV[1] += (y & 1) ? 0.5 : 0.0;
        maxUV[1] += (y & 1) ? 0.5 : 0.0;

        return TileFactory::instance()->get_tile(loader, zoom - 1, x >> 1, y >> 1);
    }

    return nullptr;
}

bool Map::Tile::valid() const
{
    return x < (uint64_t(1) << zoom) && y < (uint64_t(1) << zoom);
}

std::string Map::Tile::get_filename(bool tms, bool zxy, const std::string &ext) const
{
    std::stringstream filename;
    filename << this->zoom << "/" << x << '/' << y << ext;
    return filename.str();
}

Map::Tile::~Tile()
{
    delete texture;
}
