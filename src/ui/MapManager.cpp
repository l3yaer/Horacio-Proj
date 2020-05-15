#include "MapManager.h"
#include <glad/glad.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Loader.h"
#include "TileFactory.h"
#include "Tile.h"
#include "Camera.h"
#include "WindowManager.h"
#include "constants.h"
#include "MapCoordinatesAdapter.h"
#include "debug/Square.h"

template<> Map::MapManager *Singleton<Map::MapManager>::_instance = nullptr;

Map::MapManager::MapManager ()
	: Singleton<MapManager> (),
	  dirty (true),
	  factory (new TileFactory),
	  loader (new Loader (19, "https://b.tile.openstreetmap.de/", ".png", "./maps/")),
	  world (glm::ortho (0.0f, (float)FRAME_SIZE, 0.0f, (float)FRAME_SIZE, 0.1f, 100.0f)),
	  camera (new Camera ({-46.65597, -23.56150, 0}))
{
  camera->speed = 0.02f;

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

  const float tile_padding = (FRAME_SIZE / 2) - TILE_SIZE / 2;

  int zoom = 10;
  Debug::Square square;
  Tile *tile = factory->get_tile_at (*loader, zoom, camera->position.y, camera->position.x);
  double tile_latitude = MapCoordinatesAdapter::tile_to_latitude (tile->y, zoom);
  double tile_longitude = MapCoordinatesAdapter::tile_to_longitude (tile->x, zoom);
  double lat_diff = (TILE_SIZE/2) + (tile_latitude - camera->position.y) * TILE_SIZE
					/ MapCoordinatesAdapter::latitude_size (camera->position.y, zoom);
  double lon_diff = (TILE_SIZE/2) + (tile_longitude - camera->position.x) * TILE_SIZE / MapCoordinatesAdapter::longitude_size (zoom);
  for (int y = -NUMBER_OF_TILES / 2; y < NUMBER_OF_TILES / 2 + 1; ++y)
	{
	  for (int x = -NUMBER_OF_TILES / 2; x < NUMBER_OF_TILES / 2 + 1; ++x)
		{
		  Tile *current = get_tile (tile->zoom, tile->x + x, tile->y - y);
		  current->position = Position (TILE_SIZE * 2 * x + lon_diff,
										TILE_SIZE * 2 * y + lat_diff,
										-1.0f);
		  current->scale = Scale (TILE_SIZE * 2, TILE_SIZE * 2, 1);
		  current->render (world, camera->matrix ());
		}
	}

  square.position = Position (-46.65597,
							  -23.56150,
							  -1.0f);
  square.scale = Scale (50, 50, 1);
  //square.render (world, camera->matrix ());
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
	  case SDLK_UP:camera->apply_movement ({0.0f, 1.0f, 0.0f});
	  break;

	  case SDLK_DOWN:camera->apply_movement ({0.0f, -1.0f, 0.0f});
	  break;

	  case SDLK_LEFT:camera->apply_movement ({-1.0f, 0.0f, 0.0f});
	  break;

	  case SDLK_RIGHT:camera->apply_movement ({1.0f, 0.0f, 0.0f});
	  break;

	  default:break;
	}
}
