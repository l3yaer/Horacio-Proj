#include <cstdio>
#include <WindowManager.h>
#include <MapManager.h>
#include <imgui/ImguiWindow.h>
#include <JobManager.h>
#include <World.h>

int main (int argv, char **args)
{
  World world({1024.0f, 1024.0f});
  JobManager job_manager;
  WindowManager window_manager (1280, 720, "HOSM");
  Map::MapManager renderer;
  ImguiWindow graphicWindow (&window_manager);
  window_manager.add_system (&renderer);
  window_manager.add_system (&graphicWindow);
  window_manager.render ();
  return 0;
}
