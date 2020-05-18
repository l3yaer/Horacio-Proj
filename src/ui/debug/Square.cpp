#include "Square.h"
#include "../Shaders.h"
#include "../Square.h"
#include "../Program.h"
#include <World.h>

Debug::Square::Square ()
	: mesh (new Shape::Square (1.0f)),
	  program (new Program (debug_square_vertex_shader_source, debug_square_fragment_shader_source))
{}

Debug::Square::~Square ()
{
  delete mesh;
  delete program;
}

void Debug::Square::render ()
{
  program->use (matrix (), World::instance().get_matrix(), World::instance().get_view());
  mesh->draw ();
}
