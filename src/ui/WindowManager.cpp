#include <glad/glad.h>
#include <SDL2/SDL_opengl.h>
#include <JobManager.h>
#include <cstdio>
#include "WindowManager.h"

template <> WindowManager *Singleton<WindowManager>::_instance = nullptr;

const int SCREEN_FPS = 30;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

void window_manager_pool_inputs(void *data)
{
	auto *manager = WindowManager::instance_ptr();
	if (manager == nullptr)
		return;

	manager->pool_inputs();
	JobManager::instance().add_job(window_manager_pool_inputs, data, JobManager::Queue::INPUT);
}

WindowManager::WindowManager(int width, int height, const char *name)
		: Singleton<WindowManager>(), width(width), height(height)
{
	running = true;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
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
	JobManager::instance().add_job(window_manager_pool_inputs, nullptr, JobManager::Queue::INPUT);

	Uint32 start_ticks = 0;
	while (running) {
		start_ticks = SDL_GetTicks();

		for (auto &renderable : renderables)
			renderable->update();

		glViewport(0, 0, width, height);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		for (auto &renderable : renderables)
			renderable->render();
		SDL_GL_SwapWindow(window);

		Uint32 frame_ticks = SDL_GetTicks() - start_ticks;
		if (frame_ticks < SCREEN_TICKS_PER_FRAME)
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frame_ticks);
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
	if (SDL_WaitEvent(&event)) {
		for (auto &renderable : renderables)
			renderable->handle_event(&event);
		if (event.type == SDL_QUIT)
			running = false;
		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
			running = false;
	}
}
