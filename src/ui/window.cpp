#include <glad/glad.h>
#include <SDL2/SDL_opengl.h>
#include <cstdio>
#include "window.h"

Window::Window(int width, int height, const char* name)
{
    running = 1;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1);

    if (!gladLoadGL()) {
        fprintf(stderr, "Failed to setup GLAD\n");
        exit(1);
    }

    this->window = window;
    this->gl_context = gl_context;
}

Window::~Window()
{
    renderables.clear();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::render()
{
    int win_width, win_height;
    SDL_GetWindowSize(window, &win_width, &win_height);
    bool done = false;
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            for(auto &renderable: renderables)
                renderable->handle_event(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        for(auto &renderable: renderables)
            renderable->update();

        glViewport(0, 0, win_width, win_height);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        for(auto &renderable: renderables)
            renderable->render();
        SDL_GL_SwapWindow(window);
    }
}

void Window::add_system(WindowRenderable<SDL_Event> *renderable)
{
    renderables.push_back(renderable);
}

SDL_Window* Window::get_window()
{
    return window;
}

SDL_GLContext* Window::get_context()
{
    return &gl_context;
}
