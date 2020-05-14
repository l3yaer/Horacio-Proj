#include <cstdio>
#include "src/ui/WindowManager.h"
#include "src/ui/MapManager.h"
#include "src/ui/imgui/ImguiWindow.h"
#include "src/ui/JobManager.h"

int main (int argv, char **args)
{
  JobManager job_manager;
  WindowManager w (1280, 720, "HOSM");
  Map::MapManager renderer;
  ImguiWindow graphicWindow (&w);
  w.add_system (&renderer);
  w.add_system (&graphicWindow);
  w.render ();
  return 0;
}
