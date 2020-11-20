#ifndef _LOADER_H_
#define _LOADER_H_

#include <cstdint>
#include <string>

class Tile;

class Loader {
private:
	Loader(const Loader &) = delete;

	uint16_t max_zoom;

	const std::string prefix;
	const std::string extension;
	const std::string dir;

	friend void loader_download_tile(void *data);

	void download_image(Tile *tile);

public:
	Loader(uint16_t max_zoom, const std::string &prefix, const std::string &extension, const std::string &dir);

	~Loader() = default;

	void load_image(Tile &tile);

	void open_image(Tile *tile);

	uint16_t get_max_zoom() const;
};

#endif //_LOADER_H_
