#ifndef NUKLEAR_WINDOW_H_
#define NUKLEAR_WINDOW_H_

#include "windowRenderable.h"

class Window;
struct nk_context;

class NuklearWindow : public virtual WindowRenderable
{
private:
    struct nk_context *ctx;
public:
    NuklearWindow(Window *);
    ~NuklearWindow();

    virtual void render();
    virtual void update();
};


#endif
