#include "Square.h"
#include "../Shaders.h"
#include "../Square.h"
#include "../Program.h"

Debug::Square::Square ()
	: mesh (new Shape::Square (1.0f)),
	  program (new Program (debug_square_vertex_shader_source, debug_square_fragment_shader_source))
{}

Debug::Square::~Square ()
{
  delete mesh;
  delete program;
}

void Debug::Square::render (const WorldMatrix &world, const ViewMatrix &view)
{
  program->use (matrix (), world, view);
  mesh->draw ();
}
