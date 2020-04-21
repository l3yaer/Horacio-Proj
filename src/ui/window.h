#ifndef WINDOW_H_
#define WINDOW_H_

#include <vector>
#include <SDL2/SDL.h>
#include "windowRenderable.h"

class Window
{
private:
    SDL_Window *window;
    std::vector<WindowRenderable<SDL_Event>*> renderables;
    int running;
    SDL_GLContext glContext;
public:
    Window(int width, int height, const char* name);
    ~Window();

    void render();
    void add_system(WindowRenderable<SDL_Event> *);
    SDL_Window *getWindow();
};

#endif
