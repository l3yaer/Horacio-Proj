#ifndef _MAPMANAGER_H_
#define _MAPMANAGER_H_

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include "WindowRenderable.h"
#include <Singleton.h>
#include <types.h>
#include "constants.h"
#include "GuiMap.h"

class Program;

class Renderer;

namespace Map
{
class Loader;

class TileFactory;

class Tile;

class Actor;

class Layer;

class MapManager : public WindowRenderable<SDL_Event>, public Singleton<MapManager> {
	typedef unsigned int MapImage;

private:
	Loader *loader;
	TileFactory *factory;
	bool dirty;
	Renderer *renderer;
	Tile *center_tile;
	Coordinate position_correction;
	Coordinate start_point;
	GuiMap map;

	void move_camera(int input);

public:
	Tile *get_tile(int zoom, int latitude, int longitude);

	MapManager();

	void render() override;

	void update(float msec) override;

	void handle_event(SDL_Event *event) override;

	MapImage get_image() const;

	Coordinate get_latlng(const Coordinate &coordinate) const;
};
} // namespace Map

#endif //_MAPMANAGER_H_
