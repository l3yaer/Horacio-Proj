#ifndef IMGUI_WINDOW_H_
#define IMGUI_WINDOW_H_

#include "windowRenderable.h"

class Window;
struct ImGuiIO;

class ImguiWindow : public virtual WindowRenderable
{
private:
    ImGuiIO *io;
public:
    ImguiWindow(Window *);
    ~ImguiWindow();

    virtual void render();
    virtual void update();
};

#endif
