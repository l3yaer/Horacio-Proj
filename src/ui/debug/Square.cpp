#include "Square.h"
#include "../Square.h"
#include "../Program.h"
#include "../ProgramManager.h"
#include <World.h>

Debug::Square::Square ()
	: mesh (new Shape::Square (1.0f))
{
	program = ProgramManager::instance().create("debug square");
}

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
