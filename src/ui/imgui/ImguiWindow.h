#ifndef IMGUI_WINDOW_H_
#define IMGUI_WINDOW_H_

#include <SDL2/SDL.h>
#include "../WindowRenderable.h"

class WindowManager;
struct ImGuiIO;

namespace Map
{
class MapManager;
}

class ImguiWindow : public virtual WindowRenderable<SDL_Event> {
private:
	SDL_Window *window;
	ImGuiIO *io;

public:
	ImguiWindow(WindowManager *);
	~ImguiWindow();

	void render() override;
	void update(float msec) override;
	void handle_event(SDL_Event *) override;
};

#endif
