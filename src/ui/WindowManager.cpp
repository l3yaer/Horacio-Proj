#include <glad/glad.h>
#include "graphics.h"
#include <cstdio>
#include "WindowManager.h"

IMPLEMENT_SINGLETON(WindowManager)

WindowManager::WindowManager(int width, int height, const char *name)
		: Singleton<WindowManager>(), width(width), height(height)
{
	running = true;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
#ifdef _OS_DARWIN
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#endif
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_WindowFlags window_flags =
			(SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Window *window =
			SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);
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

WindowManager::~WindowManager()
{
	renderables.clear();

	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void WindowManager::render()
{
	SDL_GetWindowSize(window, &width, &height);

	Uint32 frame_ticks = 0;
	while (running) {
		Uint32 start_ticks = SDL_GetTicks();
		pool_inputs();

		for (auto &renderable : renderables)
			renderable->update(frame_ticks);

		glViewport(0, 0, width, height);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		for (auto &renderable : renderables)
			renderable->render();
		SDL_GL_SwapWindow(window);

		Uint32 delay_ticks = SDL_GetTicks() - start_ticks;
		if (delay_ticks < screen_ticks_per_frame)
			SDL_Delay(screen_ticks_per_frame - delay_ticks);

		frame_ticks = SDL_GetTicks() - start_ticks;
	}
}

void WindowManager::add_system(WindowRenderable<SDL_Event> *renderable)
{
	renderables.push_back(renderable);
}

SDL_Window *WindowManager::get_window()
{
	return window;
}

SDL_GLContext *WindowManager::get_context()
{
	return &gl_context;
}

void WindowManager::pool_inputs()
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		for (auto &renderable : renderables)
			renderable->handle_event(&event);
		if (event.type == SDL_QUIT)
			running = false;
		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
			running = false;
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			running = false;
	}
}
