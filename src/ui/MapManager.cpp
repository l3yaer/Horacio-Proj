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
#include "Layer.h"
#include "Renderer.h"

template <> Map::MapManager *Singleton<Map::MapManager>::_instance = nullptr;

int zoom = 15;

Map::MapManager::MapManager()
		: Singleton<MapManager>(), dirty(true), factory(new TileFactory),
		  loader(new Loader(19, "https://b.tile.openstreetmap.de/", ".png", "./maps/")), renderer(new Renderer()),
		  map_layer(new Layer())
{
	World::instance().move_to({ 51.505, -0.09 });
}

void Map::MapManager::render()
{
	renderer->begin();

	renderer->setup_map();

	renderer->draw_node(map_layer);
	render_tiles();

	renderer->end();
	dirty = false;
}

void Map::MapManager::render_tiles()
{
	for (auto *tile : map.tiles) {
		renderer->draw_node(tile);
	}
}

void Map::MapManager::update()
{
	if (dirty) {
		start_point = World::instance().get_position();
		map.go_to(start_point, 13);
		for (Tile *tile : map.tiles)
			map_layer->add_child(tile);
	}

	Coordinate new_position = World::instance().get_position();
	position_correction = new_position - start_point;

	map_layer->position += Position(position_correction, 0);

	for (auto *tile : map.tiles) {
		loader->open_image(tile);
	}

	map_layer->update(0);

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
		World::instance().add_position({ 1f, 0.0f });
		break;

	case SDLK_DOWN:
		World::instance().add_position({ -0.0002f, 0.0f });
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
