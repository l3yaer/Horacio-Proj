#include "World.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

template<> World *Singleton<World>::_instance = nullptr;

WorldMatrix World::get_matrix () const
{
  return matrix;
}
ViewMatrix World::get_view () const
{
  return camera->matrix ();
}

World::World (Size2D size)
	: matrix (glm::ortho (0.0f, size.x, 0.0f, size.y , 0.1f, 100.0f)),
	  camera (new Camera ())
{
  camera->speed = 0.0f;
}

World::~World ()
{
  delete camera;
}

Coordinate World::get_position () const
{
  return position;
}

void World::move_to (Coordinate position)
{
	this->position = position;
}

void World::add_position (Coordinate delta)
{
	position += delta;
}
