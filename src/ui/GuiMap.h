#ifndef _GUIMAP_H_
#define _GUIMAP_H_

#include <vector>
#include <types.h>

typedef std::pair<Coordinate, Coordinate> Bounds;

namespace Map
{
class Tile;
};

class GuiMap {
private:
	int zoom;
	Coordinate center;
	Coordinate pane;
	Coordinate pixel;
	Coordinate origin;

	void reset_map(Coordinate coordinate);
	Coordinate pixel_origin(Coordinate coordinate);
	Bounds tile_pixel_bounds();
	Bounds pixels_to_tile(const Bounds &pixels);
	void add_tiles(std::vector<Position> &coordinates, double y_sum);

public:
	std::vector<Map::Tile *> tiles;
	void go_to(Coordinate coordinate, int zoom);
};

#endif //_GUIMAP_H_
