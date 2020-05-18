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
#include "Renderable.h"
#include "debug/Square.h"
#include "World.h"

template<> Map::MapManager *Singleton<Map::MapManager>::_instance = nullptr;

Debug::Square *square;

Map::MapManager::MapManager ()
	: Singleton<MapManager> (),
	  dirty (true),
	  factory (new TileFactory),
	  loader (new Loader (19, "https://b.tile.openstreetmap.de/", ".png", "./maps/"))
{
  square = new Debug::Square ();
  World::instance ().move_to({-46.65597, -23.56150});

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

void Map::MapManager::render ()
{
  glViewport (0, 0, FRAME_SIZE, FRAME_SIZE);
  glBindFramebuffer (GL_FRAMEBUFFER, FBO);
  glEnable (GL_DEPTH_TEST);

  glClearColor (0.2f, 0.3f, 0.3f, 1.0f);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  int zoom = 15;
  Tile *tile = factory->get_tile_at (*loader, zoom, World::instance ().get_position().y, World::instance ().get_position().x);
  Coordinate position_correction = MapCoordinatesAdapter::calculate_position_correction ({tile->x, tile->y},
																						 zoom,
																						 World::instance ().get_position());
  int tile_range = NUMBER_OF_TILES / 2;
  for (int y = -tile_range; y < tile_range + 1; ++y)
	{
	  for (int x = -tile_range; x < tile_range + 1; ++x)
		{
		  Tile *current = get_tile (tile->zoom, tile->x + x, tile->y - y);
		  current->position = Position (MapCoordinatesAdapter::coord_to_screen ({x, y}, position_correction),
										-99.0f);
		  current->scale = Scale (TILE_SIZE, TILE_SIZE, 1);
		  current->render ();
		}
	}
  glBindFramebuffer (GL_FRAMEBUFFER, 0);
  glDisable (GL_DEPTH_TEST);
  glViewport (0, 0, WindowManager::instance ().width, WindowManager::instance ().height);
  dirty = false;
}

void Map::MapManager::update ()
{
}

void Map::MapManager::handle_event (SDL_Event *event)
{
  switch (event->type)
	{
	  case SDL_KEYDOWN:dirty = true;
	  moveCamera (event->key.keysym.sym);
	  break;
	}
}

Map::Tile *Map::MapManager::get_tile (int zoom, int latitude, int longitude)
{
  return factory->get_tile (*loader, zoom, latitude, longitude);
}

void Map::MapManager::moveCamera (int input)
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
