#include <cstdio>
#include <WindowManager.h>
#include <MapManager.h>
#include <imgui/ImguiWindow.h>
#include <JobManager.h>
#include <TextureManager.h>
#include <MeshManager.h>
#include <ProgramManager.h>
#include <World.h>
#include <GuiMap.h>
#include <LogManager.h>

int main(int argv, char **args)
{
	LogManager log_manager;
	log_manager.create_log("debug", true);
	World world(MAP_SIZE);
	JobManager job_manager;
	TextureManager texture_manager;
	ProgramManager program_manager;
	MeshManager mesh_manager;
	WindowManager window_manager(1280, 720, "Horacio Project");
	MapManager renderer;
	ImguiWindow graphicWindow(&window_manager);
	window_manager.add_system(&renderer);
	window_manager.add_system(&graphicWindow);
	window_manager.render();
	return 0;
}
