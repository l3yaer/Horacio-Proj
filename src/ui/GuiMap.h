#ifndef _GUIMAP_H_
#define _GUIMAP_H_

#include <vector>
#include <types.h>
#include <SceneNode.h>

typedef std::pair<Coordinate, Coordinate> Bounds;

class Actor;

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

	Coordinate get_origin(const Coordinate &coordinate) const;

	Map::Layer *tile_layer;

	Map::Layer *actor_layer;
public:
	GuiMap();
	~GuiMap();

	std::vector<Map::Tile *> tiles;
	std::vector<Actor *> actors;

	void go_to(Coordinate coordinate, int zoom);
	void spawn_actor(Actor *actor);

	void update(float msec) override;
	void render() override;
};

#endif //_GUIMAP_H_
