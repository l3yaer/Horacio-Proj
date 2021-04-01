#include <iostream>
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
#include <Rete.h>

int main(int argv, char **args)
{
	/*
	Rete::Net rete;

	Rete::ProductionNode *prod2 = rete.add({
			Rete::Condition("?x", "color", "blue")
		}, "prod2");

	Rete::ProductionNode *prod = rete.add({
			Rete::Condition("?x", "on", "?y"),
			Rete::Condition("?x", "color", "blue")
		}, "prod1");

	rete.remove(prod2);

	rete.add(new Rete::WME("B1", "color", "blue"));
	Rete::WME *b1 = new Rete::WME("B1", "on", "B2");
	rete.add(b1);
	rete.add(new Rete::WME("B1", "on", "B3"));
	rete.add(new Rete::WME("B2", "on", "table"));
	rete.add(new Rete::WME("B2", "color", "blue"));
	rete.add(new Rete::WME("B3", "color", "red"));

	std::cout << rete << std::endl;
	*/

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
