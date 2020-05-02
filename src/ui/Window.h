#ifndef WINDOW_H_
#define WINDOW_H_

#include <vector>
#include <SDL2/SDL.h>
#include "WindowRenderable.h"

class Window
{
private:
    SDL_Window *window;
    std::vector<WindowRenderable<SDL_Event>*> renderables;
    int running;
    SDL_GLContext gl_context;
public:
    Window(int width, int height, const char* name);
    ~Window();

    void render();
    void add_system(WindowRenderable<SDL_Event> *);
    SDL_Window *get_window();
    SDL_GLContext *get_context();
};

#endif
