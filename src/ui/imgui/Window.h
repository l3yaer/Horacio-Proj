#ifndef IMGUI_WINDOW_H_
#define IMGUI_WINDOW_H_

#include <SDL2/SDL.h>
#include "../WindowRenderable.h"

class Window;
struct ImGuiIO;

namespace Map { class MapRenderer; }

class ImguiWindow : public virtual WindowRenderable<SDL_Event>
{
private:
    SDL_Window *window;
    ImGuiIO *io;
public:
    ImguiWindow(Window*);
    ImguiWindow(Window*, Map::MapRenderer*);
    ~ImguiWindow();

    void render() override;
    void update() override;
    void handle_event(SDL_Event *) override;
};

#endif
