#include "ImguiWindow.h"
#include <imgui.h>
#include <World.h>
#include <LogManager.h>
#include "../WindowManager.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "../MapManager.h"
#include "../TextureManager.h"
#include "../constants.h"

ImguiWindow::ImguiWindow(WindowManager *window)
{
	this->window = window->get_window();
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &iol = ImGui::GetIO();
	(void)iol;

	this->io = &iol;
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(window->get_window(), *window->get_context());
	ImGui_ImplOpenGL3_Init("#version 130");
}

ImguiWindow::~ImguiWindow()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void ImguiWindow::update(float msec)
{
	Coordinate mouse_pos;
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(window);
	ImGui::NewFrame();
	{
		ImGui::Begin("Map Window");
		{
			ImVec2 pos = ImGui::GetCursorScreenPos();
			Coordinate mouse = {io->MousePos.x - pos.x - 4, (io->MousePos.y - pos.y) + 4};
			mouse_pos = Map::MapManager::instance().get_latlng(mouse);
			ImGui::GetWindowDrawList()->AddImage((void *)Map::MapManager::instance().get_image(), pos,
												 ImVec2(pos.x + MAP_WIDTH, pos.y + MAP_HEIGHT), ImVec2(0, 1),
												 ImVec2(1, 0));
		}
		ImGui::End();

		ImGui::Begin("Info");
		{
			ImGui::Text("Current position: %3.5f, %3.5f", World::instance().get_position().x,
						World::instance().get_position().y);
			ImGui::Text("Textures memory usage: %zu B", TextureManager::instance().get_memory_usage());

			ImGui::Text("Mouse coordinates: %3.5f, %3.5f", mouse_pos.x, mouse_pos.y);

			static float actor_pos[2];
			ImGui::Button("Place actor");
			ImGui::SameLine();
			ImGui::InputFloat2("", actor_pos);
		}
		ImGui::End();

		ImGui::Begin("Log");
		{
			ImGui::BeginChild("Log scroll");
            std::string log = LogManager::instance().get_default_log()->contents();
            ImGui::Text((log.size() > 2048 ? log.substr(log.size() - 2048) : log).c_str());
			ImGui::EndChild();
		}
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
	ImGui::Render();
}

void ImguiWindow::render()
{
	ImDrawData *draw_data = ImGui::GetDrawData();
	if (draw_data)
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiWindow::handle_event(SDL_Event *event)
{
	ImGui_ImplSDL2_ProcessEvent(event);
}
