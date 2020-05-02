#include <stdio.h>
#include "src/fsm.h"
#include "src/ui/Window.h"
#include "src/ui/MapRenderer.h"
#include "src/ui/imgui/Window.h"

int main(int argv, char** args)
{
    Window w(1280, 720, "FSM Manager");
    Map::MapRenderer renderer;
    ImguiWindow graphicWindow(&w, &renderer);
    w.add_system(&renderer);
    w.add_system(&graphicWindow);
    w.render();
    return 0;
}
