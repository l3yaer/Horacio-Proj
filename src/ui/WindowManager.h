#ifndef _WINDOWMANAGER_H_
#define _WINDOWMANAGER_H_

#include <vector>
#include <SDL2/SDL.h>
#include "WindowRenderable.h"
#include <Singleton.h>

class WindowManager : public Singleton<WindowManager> {
    private:
	SDL_Window *window;
	std::vector<WindowRenderable<SDL_Event> *> renderables;
	bool running;
	SDL_GLContext gl_context;

    public:
	int width, height;

	WindowManager(int width, int height, const char *name);
	~WindowManager();

	void render();
	void add_system(WindowRenderable<SDL_Event> *);
	SDL_Window *get_window();
	SDL_GLContext *get_context();

    private:
	void pool_inputs();

    private:
	friend void window_manager_pool_inputs(void *data);
};

#endif
