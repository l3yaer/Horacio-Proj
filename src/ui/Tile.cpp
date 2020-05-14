//
// Created by horacio on 4/30/20.
//

#include <sstream>
#include "Tile.h"
#include "Texture.h"

Map::Tile::Tile(uint16_t zoom, int latitude, int longitude, Texture *texture) : zoom(zoom),
                                                                                latitude(latitude),
                                                                                longitude(longitude),
                                                                                texture(texture) {}

bool Map::Tile::valid() const
{
    return latitude < (uint64_t(1) << zoom) && longitude < (uint64_t(1) << zoom);
}

std::string Map::Tile::get_filename(const std::string &ext) const
{
    std::stringstream filename;
    filename << zoom << "/" << latitude << '/' << longitude << ext;
    return filename.str();
}

Map::Tile::~Tile()
{
    delete texture;
}

void Map::Tile::render(const WorldMatrix &world,const ViewMatrix& view)
{
    if(texture) texture->use();
    program->use(matrix(), world, view);
    mesh->draw();
}
