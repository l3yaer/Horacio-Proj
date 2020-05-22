#ifndef _MAPMANAGER_H_
#define _MAPMANAGER_H_

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include "WindowRenderable.h"
#include <Singleton.h>
#include <types.h>
#include "constants.h"

class Program;

namespace Map
{
class Loader;

class MapRenderer;

class TileFactory;

class Tile;

class Actor;

class MapManager : public WindowRenderable<SDL_Event>, public Singleton<MapManager>
{
	typedef unsigned int MapImage;
 private:
	Loader *loader;
	TileFactory *factory;
	bool dirty;
	MapRenderer *renderer;
	Tile *center_tile;
	Coordinate position_correction;
	//std::vector<Actor *> actors;

	Tile *get_tile (int zoom, int latitude, int longitude);

	void move_camera (int input);

	void render_tiles ();
 public:

	MapManager ();

	void render () override;

	void update () override;

	void handle_event (SDL_Event *event) override;

	MapImage get_image () const;
};
}

#endif //_MAPMANAGER_H_
