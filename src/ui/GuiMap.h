#ifndef _GUIMAP_H_
#define _GUIMAP_H_

#include <vector>
#include <types.h>
#include "SceneNode.h"

typedef std::pair<Coordinate, Coordinate> Bounds;

namespace Map
{
class Tile;

class Layer;
}; // namespace Map

class GuiMap : public SceneNode {
private:
	int zoom;
	Coordinate center;
	Coordinate current;
	Coordinate origin;

	void reset_map(Coordinate coordinate);
	Bounds tile_pixel_bounds();
	Bounds pixels_to_tile(const Bounds &pixels);
	void add_tiles(std::vector<Position> &coordinates, double y_sum);

	Coordinate get_center(const Bounds &bounds) const;

	Coordinate get_origin(const Coordinate &coordinate) const;

	Map::Layer *tile_layer;

public:
	GuiMap();
	~GuiMap();

	std::vector<Map::Tile *> tiles;
	void go_to(Coordinate coordinate, int zoom);

	void update(float msec) override;
	void render() override;
};

#endif //_GUIMAP_H_
