#include "imguiWindow.h"
#include <imgui.h>
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "window.h"

ImguiWindow::ImguiWindow(Window* window)
{
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window->getWindow(), true);

    io = &ImGui::GetIO();
    io->MouseDrawCursor = true;
}

ImguiWindow::~ImguiWindow()
{
    ImGui_ImplGlfwGL3_Shutdown();

    ImGui::DestroyContext();
}

void ImguiWindow::render()
{
    ImGui::Render();
}


void ImguiWindow::update()
{
    ImGui_ImplGlfwGL3_NewFrame();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io->DisplaySize);
    ImGui::Begin("Content", nullptr,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings |
                 ImGuiWindowFlags_NoBringToFrontOnFocus);

    ImGui::End();
}
