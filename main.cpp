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
#include <ReteNet.h>

int main(int argv, char **args)
{

	ReteNet net;
	net.add({
		// production
		{ "?x", ".color", "blue" },
	}, {
		// display when match
		{ "%", "print", "kek"},
		{ "?x", ".is", "awesome" },
	});
	net.add({
		// production
		{ "?x", ".on", "?y" },
		{ "?y", ".left-of", "?z" },
		{ "?z", ".color", "red" },
	}, {
		// display when match
		{ "%", "print", "oh no"},
		{ "?y", ".structure", "broken" },
	});

	net.add({ "B1", ".on", "B2" });
	net.add({ "B1", ".on", "B3" });
	net.add({ "B1", ".color", "red" });

	net.add({ "B2", ".on", "table" });
	net.add({ "B2", ".left-of", "B3" });
	net.add({ "B2", ".color", "blue" });

	net.add({ "B3", ".left-of", "B4" });
	net.add({ "B3", ".on", "table" });
	net.add({ "B3", ".color", "red" });

	for (auto conds : net.run())
		for (auto cond : conds) {
			cond.print();
		}
	/*
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
	*/
	return 0;
}
