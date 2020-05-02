#include "Window.h"
#include "../Window.h"
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <imgui.h>
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "../MapRenderer.h"

unsigned int FBO = 0;

ImguiWindow::ImguiWindow(Window *window)
{
    this->window = window->get_window();
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &iol = ImGui::GetIO();
    (void) iol;

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

void ImguiWindow::update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();
    {
        ImGui::Begin("Another Window");
        ImGui::GetWindowDrawList()->AddImage((void*) FBO, ImVec2(ImGui::GetCursorPos()),
                                             ImVec2(ImGui::GetCursorScreenPos().x + 400.0f,
                                                    ImGui::GetCursorScreenPos().y + 300.0f), ImVec2(0, 1),
                                             ImVec2(1, 0));
        ImGui::End();
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

ImguiWindow::ImguiWindow(Window *window, Map::MapRenderer *map_renderer)
{
    this->window = window->get_window();
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &iol = ImGui::GetIO();
    (void) iol;

    this->io = &iol;
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(window->get_window(), *window->get_context());
    ImGui_ImplOpenGL3_Init("#version 130");

    FBO = map_renderer->FBO;
}
