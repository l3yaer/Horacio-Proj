#ifndef NUKLEAR_WINDOW_H_
#define NUKLEAR_WINDOW_H_

#include "windowRenderable.h"
#include <SDL2/SDL.h>

class Window;
struct nk_context;

class NuklearWindow : public virtual WindowRenderable<SDL_Event>
{
private:
    struct nk_context *ctx;
public:
    explicit NuklearWindow(Window *);
    ~NuklearWindow();

    void render() override;
    void update() override;
    void handle_event(SDL_Event *event) override;
};


#endif
