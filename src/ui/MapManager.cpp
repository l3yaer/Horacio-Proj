#include "MapManager.h"
#include <LogManager.h>
#include "TileFactory.h"
#include "WindowManager.h"
#include "constants.h"
#include "SphericalMercator.h"
#include "World.h"
#include "GuiActor.h"
#include "Layer.h"
#include "Renderer.h"
#include "RegularPolygon.h"
#include "VectorArea.h"
#include "NodeRendererVisitor.h"
#include "NodeVisitor.h"
#include <MoveAction.h>

IMPLEMENT_SINGLETON(MapManager)

MapManager::MapManager()
	: Singleton<MapManager>(), dirty(true), renderer(new Renderer()),
	  map(GuiMap(new TileFactory("https://b.tile.openstreetmap.de/", ".png", "./maps/")))
{
	World::instance().move_to({ 51.505, -0.159 });
	start_point = World::instance().get_position();
}

void MapManager::render()
{
	NodeRendererVisitor visitor(renderer);
	renderer->begin();
	dynamic_cast<VisitableNode*>(&map)->accept(visitor);
	renderer->end();
	dirty = false;
}

void MapManager::update(float msec)
{
	Coordinate new_position = World::instance().get_position();

	if (dirty) {
		start_point = World::instance().get_position();
		map.go_to({start_point, 15});
		GuiActor *a = new GuiActor("a1", Position(51.502, -0.159, -1.0), Scale(20.0, 20.0, 1.0));
		map.spawn(a);
		map.spawn(new VectorArea("a1", Position(51.503, -0.159, -1.0), Scale(20.0, 20.0, 1.0), 5, {1,1,0}, 0.6));
		map.spawn(new VectorArea("a1", Position(51.504, -0.159, -1.0), Scale(20.0, 20.0, 1.0), 5, {1,0,1}, 0.5));
		map.spawn(new VectorArea("a1", Position(51.505, -0.159, -1.0), Scale(20.0, 20.0, 1.0), 5, {0,1,0}, 0.4));
		map.spawn(new VectorArea("a1", Position(51.506, -0.159, -1.0), Scale(20.0, 20.0, 1.0), 5, {0,0,1}, 0.3));

		MoveAction *mv = new MoveAction(a, {20,20,-1}, 5);
		a->add_action(mv);
	}

	map.update(msec);

	start_point = new_position;
}

void MapManager::handle_event(SDL_Event *event)
{
	switch (event->type) {
	case SDL_KEYDOWN: //dirty = true;
		move_camera(event->key.keysym.sym);
		break;
	}
}

void MapManager::move_camera(int input)
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

	case SDLK_MINUS:
	case SDLK_KP_MINUS:
		map.set_zoom(std::max(0, map.get_zoom() - 1));
		break;

	case SDLK_PLUS:
	case SDLK_KP_PLUS:
		map.set_zoom(std::min(19, map.get_zoom() + 1));
		break;
	default:
		break;
	}
}

MapManager::MapImage MapManager::get_image() const
{
	return renderer->frame;
}

Coordinate MapManager::get_latlng(const Coordinate &coordinate) const
{
	return SphericalMercator::point_to_coordinate(coordinate + map.origin, map.get_zoom());
}
