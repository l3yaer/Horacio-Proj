//
// Created by horacio on 4/30/20.
//

#include <sstream>
#include "Tile.h"
#include "TileFactory.h"
#include "Texture.h"

Map::Tile::Tile(uint16_t zoom, int latitude, int longitude, Texture *texture) : zoom(zoom),
                                                                                latitude(latitude),
                                                                                longitude(longitude),
                                                                                texture(texture) {}

Map::Tile *Map::Tile::get(Map::Loader &loader, int dx, int dy)
{
    if (zoom > 0)
        return TileFactory::instance()->get_tile(loader, zoom, latitude+dx, longitude+dy);
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
        return TileFactory::instance()->get_tile(loader, zoom - 1, latitude >> 1, longitude >> 1);
    return nullptr;
}

Map::Tile *Map::Tile::get_parent(Map::Loader &loader, float *minUV, float *maxUV) const
{
    if (zoom > 0)
    {
        minUV[0] *= 0.5;
        maxUV[0] *= 0.5;
        minUV[0] += (latitude & 1) ? 0.5 : 0.0;
        maxUV[0] += (longitude & 1) ? 0.5 : 0.0;

        minUV[1] *= 0.5;
        maxUV[1] *= 0.5;
        minUV[1] += (latitude & 1) ? 0.5 : 0.0;
        maxUV[1] += (longitude & 1) ? 0.5 : 0.0;

        return TileFactory::instance()->get_tile(loader, zoom - 1, latitude >> 1, longitude >> 1);
    }

    return nullptr;
}

bool Map::Tile::valid() const
{
    return latitude < (uint64_t(1) << zoom) && longitude < (uint64_t(1) << zoom);
}

std::string Map::Tile::get_filename(bool tms, bool zxy, const std::string &ext) const
{
    std::stringstream filename;
    filename << this->zoom << "/" << latitude << '/' << longitude << ext;
    return filename.str();
}

Map::Tile::~Tile()
{
    delete texture;
}

void Map::Tile::render(WorldMatrix &world)
{
    texture->use();
    program->use(getMatrix(), world);
    mesh->draw();
}
