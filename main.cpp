#include <stdio.h>
#include "src/fsm.h"
#include "src/ui/window.h"
#include "src/ui/imgui/window.h"

int main(int argv, char** args)
{
    Window w(1280, 720, "FSM Manager");
    ImguiWindow graphicWindow(&w);
    w.add_system(&graphicWindow);
    w.render();
    return 0;
}
