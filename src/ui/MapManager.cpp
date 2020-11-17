#include "MapManager.h"
#include <glad/glad.h>
#include <iostream>
#include <LogManager.h>
#include "Loader.h"
#include "TileFactory.h"
#include "Tile.h"
#include "Camera.h"
#include "WindowManager.h"
#include "constants.h"
#include "World.h"
#include "GuiActor.h"
#include "Layer.h"
#include "Renderer.h"

template <> Map::MapManager *Singleton<Map::MapManager>::_instance = nullptr;

int zoom = 15;

Map::MapManager::MapManager()
		: Singleton<MapManager>(), dirty(true), factory(new TileFactory),
		  loader(new Loader(19, "https://b.tile.openstreetmap.de/", ".png", "./maps/")), renderer(new Renderer())
{
	World::instance().move_to({ 51.504, -0.159 });
	start_point = World::instance().get_position();
}

void Map::MapManager::render()
{
	renderer->begin();

	renderer->draw_node(&map);

	renderer->setup(Renderer::Programs::TILE);
	for (auto *tile : map.tiles)
		renderer->draw_node(tile);

	renderer->setup(Renderer::Programs::ACTOR);
	for (auto *actor : map.actors)
		renderer->draw_node(actor);

	renderer->end();
	dirty = false;
}

void Map::MapManager::update(float msec)
{
	Coordinate new_position = World::instance().get_position();

	if (dirty) {
		start_point = World::instance().get_position();
		map.go_to(start_point, zoom);

		GuiActor *a1 = new GuiActor("a1", Position(51.504, -0.159, -1.0), Scale(20.0, 20.0, 1.0));
		map.spawn_actor(a1);
	}

	for (auto *tile : map.tiles)
		loader->open_image(tile);

	map.update(msec);

	start_point = new_position;
}

void Map::MapManager::handle_event(SDL_Event *event)
{
	switch (event->type) {
	case SDL_KEYDOWN: //dirty = true;
		move_camera(event->key.keysym.sym);
		break;
	}
}

Map::Tile *Map::MapManager::get_tile(int zoom, int latitude, int longitude)
{
	return factory->get_tile(*loader, zoom, latitude, longitude);
}

void Map::MapManager::move_camera(int input)
{
	switch (input) {
	case SDLK_UP:
		World::instance().add_position({ -0.0002f, 0.0f });
		break;

	case SDLK_DOWN:
		World::instance().add_position({ 0.0002f, 0.0f });
		break;

	case SDLK_LEFT:
		World::instance().add_position({ 0.0f, -0.0002f });
		break;

	case SDLK_RIGHT:
		World::instance().add_position({ 0.0f, 0.0002f });
		break;

	default:
		break;
	}
}

Map::MapManager::MapImage Map::MapManager::get_image() const
{
	return renderer->frame;
}
