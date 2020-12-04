#ifndef _GUIMAP_H_
#define _GUIMAP_H_

#include <vector>
#include <types.h>
#include <Actor.h>
#include <Map.h>
#include "NodeVisitor.h"

class TileFactory;

class GuiMap : public Map, public VisitableNodeImpl<GuiMap> {
private:
	int zoom;

	Bounds tile_pixel_bounds();
	Bounds pixels_to_tile(const Bounds &pixels);
	void add_tile(const Position &coordinate, double y_sum);

	Coordinate get_origin(const Coordinate &coordinate) const;

	Layer *tile_layer;
	TileFactory *tile_factory;
public:
	GuiMap(TileFactory *);
	~GuiMap();

	Coordinate origin;

	std::vector<Tile *> tiles;

	void go_to(Position position) override;
	void spawn(Actor *actor) override;
	void spawn(Area *actor) override;

	void update(float msec) override;
	void render() override;

	int get_zoom() const;
	void set_zoom(int zoom);
};

#endif //_GUIMAP_H_
