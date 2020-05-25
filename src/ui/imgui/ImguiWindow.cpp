#include "ImguiWindow.h"
#include <imgui.h>
#include "../WindowManager.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "../MapManager.h"
#include "../TextureManager.h"

ImguiWindow::ImguiWindow (WindowManager *window)
{
	this->window = window->get_window ();
	IMGUI_CHECKVERSION();
	ImGui::CreateContext ();
	ImGuiIO &iol = ImGui::GetIO ();
	(void)iol;

	this->io = &iol;
	ImGui::StyleColorsDark ();

	ImGui_ImplSDL2_InitForOpenGL (window->get_window (), *window->get_context ());
	ImGui_ImplOpenGL3_Init ("#version 130");
}

ImguiWindow::~ImguiWindow ()
{
	ImGui_ImplOpenGL3_Shutdown ();
	ImGui_ImplSDL2_Shutdown ();
	ImGui::DestroyContext ();
}

void ImguiWindow::update ()
{
	ImGui_ImplOpenGL3_NewFrame ();
	ImGui_ImplSDL2_NewFrame (window);
	ImGui::NewFrame ();
	{
		ImGui::Begin ("Map Window");
		{
			ImVec2 pos = ImGui::GetCursorScreenPos ();

			ImGui::GetWindowDrawList ()->AddImage ((void *)Map::MapManager::instance ().get_image (),
																						 pos,
																						 ImVec2 (pos.x + 800, pos.y + 800),
																						 ImVec2 (0, 1),
																						 ImVec2 (1, 0));
		}
		ImGui::End ();

		ImGui::Begin ("Info");
		{
			ImGui::Text("Textures memory usage: %zu KB", TextureManager::instance().get_memory_usage()/1024);
		}
		ImGui::End ();
	}
	ImGui::Render ();
}

void ImguiWindow::render ()
{
	ImDrawData *draw_data = ImGui::GetDrawData ();
	if (draw_data)
		ImGui_ImplOpenGL3_RenderDrawData (ImGui::GetDrawData ());
}

void ImguiWindow::handle_event (SDL_Event *event)
{
	ImGui_ImplSDL2_ProcessEvent (event);
}