#include <stdio.h>
#include "src/fsm.h"
#include "src/ui/window.h"
#include "./src/ui/nuklearWindow.h"

int main(int argv, char** args)
{
    Window w(1280, 720, "FSM Manager");
    NuklearWindow graphicWindow(&w);
    w.add_system(&graphicWindow);
    w.render();
    return 0;
}
