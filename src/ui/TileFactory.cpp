#include "TileFactory.h"
#include <glad/glad.h>
#include <sstream>
#include <math.h>
#include "Tile.h"
#include "Loader.h"

std::string vertex_shader_source = "#version 330 core\n"
                                   "layout (location = 0) in vec3 aPos;\n"
                                   "layout (location = 1) in vec2 aTexCoord;\n"
                                   "out vec3 ourColor;\n"
                                   "out vec2 TexCoord;\n"
                                   "uniform mat4 model;\n"
                                   "uniform mat4 projection;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   gl_Position = projection * model * vec4(aPos, 1.0);\n"
                                   "   TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
                                   "}";

std::string fragment_shader_source = "#version 330 core\n"
                                     "out vec4 FragColor;\n"
                                     "in vec2 TexCoord;\n"
                                     "uniform sampler2D texture1;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    FragColor = texture(texture1, TexCoord);\n"
                                     "}";


Map::TileFactory *Map::TileFactory::_instance = nullptr;

Map::TileFactory::TileFactory() : square(new Shape::Square(1.0f)),
                                  program(new Program(vertex_shader_source, fragment_shader_source)) {}

Map::TileFactory::~TileFactory()
{
    for (const auto &i : tiles)
    {
        delete i.second;
    }
    tiles.clear();
}

std::string Map::TileFactory::tile_id(uint16_t zoom, uint64_t x, uint64_t y)
{
    std::stringstream ss;
    ss << zoom << "/" << x << "/" << y;
    return ss.str();
}

Map::TileFactory *Map::TileFactory::instance()
{
    static CGuard g;
    if (!_instance)
    {
        _instance = new TileFactory();
    }
    return _instance;
}

Map::Tile *Map::TileFactory::get_tile(Loader &loader, uint16_t zoom, int x, int y)
{
    std::string id = tile_id(zoom, x, y);
    auto key = std::make_pair(&loader, id);
    auto i = tiles.find(key);
    if (i != tiles.end())
    {
        return i->second;
    }
    Tile *tile = new Tile(zoom, x, y, nullptr);
    loader.load_image(*tile);
    tile->mesh = square;
    tile->program = program;
    tiles[key] = tile;
    return tile;
}

int long2tilex(double lon, int z)
{
    return (int) (floor((lon + 180.0) / 360.0 * (1 << z)));
}

int lat2tiley(double lat, int z)
{
    double latrad = lat * M_PI / 180.0;
    return (int) (floor((1.0 - asinh(tan(latrad)) / M_PI) / 2.0 * (1 << z)));
}

double tilex2long(int x, int z)
{
    return x / (double) (1 << z) * 360.0 - 180;
}

double tiley2lat(int y, int z)
{
    double n = M_PI - 2.0 * M_PI * y / (double) (1 << z);
    return 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
}

Map::Tile *Map::TileFactory::get_tile_at(Loader &loader, uint16_t zoom, double x, double y)
{
    return get_tile(loader, zoom, lat2tiley(x, zoom), long2tilex(y, zoom));
}
