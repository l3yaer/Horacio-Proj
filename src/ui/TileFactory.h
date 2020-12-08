#ifndef _TILEFACTORY_H_
#define _TILEFACTORY_H_

#include <string>
#include <map>
#include <cstdint>

class Program;

class Loader;

class Tile;

class TileFactory {
private:
	std::map<std::string, Tile *> tiles;
	const std::string prefix;
	const std::string extension;
	const std::string dir;

	TileFactory(const TileFactory &)
	{
	}

	~TileFactory();

	static std::string tile_id(uint16_t zoom, uint64_t x, uint64_t y);

	friend void texture_factory_download_tile(void *data);

	void download_image(Tile *tile);

	void load_image(Tile &tile);

public:
	TileFactory(const std::string &prefix, const std::string &extension, const std::string &dir);

	Tile *get_tile(uint16_t zoom, int x, int y);

	void open_image(Tile *tile);
};

#endif //_TILEFACTORY_H_
