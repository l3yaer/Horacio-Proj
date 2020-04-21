#include <glad/glad.h>
#include <SDL2/SDL_opengl.h>
#include <cstdio>
#include "window.h"


Window::Window(int width, int height, const char* name)
{
    running = 1;

    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    window = SDL_CreateWindow(name,
                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                           width, height, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);
    glContext = SDL_GL_CreateContext(window);

    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        fprintf(stderr, "Failed to setup GLAD\n");
        exit(1);
    }
}

Window::~Window()
{
    renderables.clear();

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::render()
{
    int win_width, win_height;
    SDL_GetWindowSize(window, &win_width, &win_height);
    while (running) {

        SDL_Event evt;
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT)
            {
                running = 0;
                break;
            }
            for(auto &renderable: renderables)
                renderable->handle_event(&evt);
        }

        if(!running) break;

        for(auto &renderable: renderables)
            renderable->update();

        SDL_GetWindowSize(window, &win_width, &win_height);
        glViewport(0, 0, win_width, win_height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        for(auto &renderable: renderables)
            renderable->render();

        SDL_GL_SwapWindow(window);
    }
}

void Window::add_system(WindowRenderable<SDL_Event> *renderable)
{
    renderables.push_back(renderable);
}

SDL_Window* Window::getWindow()
{
    return window;
}
