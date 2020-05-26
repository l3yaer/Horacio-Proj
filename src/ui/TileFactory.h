#ifndef _TILEFACTORY_H_
#define _TILEFACTORY_H_

#include <string>
#include <map>
#include <cstdint>


class Mesh;

class Program;

namespace Map
{

class Loader;

class Tile;

class TileFactory
{
 private:
  std::map<std::string, Tile *> tiles;

  Mesh *square;

  TileFactory (const TileFactory &)
  {}

  ~TileFactory ();

  static std::string tile_id (uint16_t zoom, uint64_t x, uint64_t y);

 public:

  TileFactory ();

  Tile *get_tile (Loader &loader, uint16_t zoom, int x, int y);

  Tile *get_tile_at (Loader &loader, uint16_t zoom, double x, double y);

};
}

#endif //_TILEFACTORY_H_
