#ifndef IMGUI_WINDOW_H_
#define IMGUI_WINDOW_H_

#include <SDL2/SDL.h>
#include "../windowRenderable.h"

class Window;
struct ImGuiIO;

class ImguiWindow : public virtual WindowRenderable<SDL_Event>
{
private:
    SDL_Window *window;
    ImGuiIO *io;
public:
    ImguiWindow(Window*);
    ~ImguiWindow();

    void render() override;
    void update() override;
    void handle_event(SDL_Event *) override;
};

#endif
