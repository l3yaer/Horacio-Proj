#include "MapManager.h"
#include <glad/glad.h>
#include <iostream>
#include "Loader.h"
#include "TileFactory.h"
#include "Tile.h"
#include "Camera.h"
#include "WindowManager.h"
#include "constants.h"
#include "MapCoordinatesAdapter.h"
#include "World.h"
#include "GuiActor.h"

template<> Map::MapManager *Singleton<Map::MapManager>::_instance = nullptr;

int zoom = 15;

namespace Map
{

class MapRenderer
{
 public:
	unsigned int FBO;
	MapRenderer ();

	void config_render () const;
	void commit () const;
};

MapRenderer::MapRenderer () : FBO (0)
{
	unsigned int TBO;
	unsigned int RBO;

	glGenFramebuffers (1, &FBO);
	glBindFramebuffer (GL_FRAMEBUFFER, FBO);

	glGenTextures (1, &TBO);
	glBindTexture (GL_TEXTURE_2D, TBO);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, FRAME_SIZE, FRAME_SIZE, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TBO, 0);

	glGenRenderbuffers (1, &RBO);
	glBindRenderbuffer (GL_RENDERBUFFER, RBO);
	glRenderbufferStorage (GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, FRAME_SIZE, FRAME_SIZE);
	glFramebufferRenderbuffer (GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
	if (glCheckFramebufferStatus (GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer (GL_FRAMEBUFFER, 0);
}

void MapRenderer::config_render () const
{
	glViewport (0, 0, FRAME_SIZE, FRAME_SIZE);
	glBindFramebuffer (GL_FRAMEBUFFER, FBO);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor (0.2f, 0.3f, 0.3f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MapRenderer::commit () const
{
	glBindFramebuffer (GL_FRAMEBUFFER, 0);
	glDisable (GL_DEPTH_TEST);
	glDisable (GL_BLEND);
	glViewport (0, 0, WindowManager::instance ().width, WindowManager::instance ().height);
}
}

Map::MapManager::MapManager ()
		: Singleton<MapManager> (),
			dirty (true),
			factory (new TileFactory),
			loader (new Loader (19, "https://b.tile.openstreetmap.de/", ".png", "./maps/")),
			renderer (new MapRenderer ())
{
	World::instance ().move_to ({51.505, -0.09});
}

void Map::MapManager::render ()
{
	renderer->config_render ();
	if(dirty) map.go_to(World::instance().get_position(), 13);

	render_tiles ();

	renderer->commit ();
	dirty = false;
}

void Map::MapManager::render_tiles ()
{
	for(auto* tile : map.tiles)
		{
			tile->render();
		}
}

void Map::MapManager::update ()
{

	center_tile = factory->get_tile_at (*loader, zoom, World::instance ().get_position ().y, World::instance ().get_position ().x);

	position_correction = MapCoordinatesAdapter::calculate_position_correction (center_tile->coordinate (),
																																							zoom,
																																							World::instance ().get_position ());

	center_point = Position (center_tile->x, center_tile->y, zoom);
}

void Map::MapManager::handle_event (SDL_Event *event)
{
	switch (event->type)
		{
			case SDL_KEYDOWN:dirty = true;
			move_camera (event->key.keysym.sym);
			break;
		}
}

Map::Tile *Map::MapManager::get_tile (int zoom, int latitude, int longitude)
{
	return factory->get_tile (*loader, zoom, latitude, longitude);
}

void Map::MapManager::move_camera (int input)
{
	switch (input)
		{
			case SDLK_UP:World::instance ().add_position ({0.0f, 0.00002f});
			break;

			case SDLK_DOWN:World::instance ().add_position ({0.0f, -0.00002f});
			break;

			case SDLK_LEFT:World::instance ().add_position ({-0.00002f, 0.0f});
			break;

			case SDLK_RIGHT:World::instance ().add_position ({0.00002f, 0.0f});
			break;

			default:break;
		}
}

Map::MapManager::MapImage Map::MapManager::get_image () const
{
	return renderer->FBO;
}
