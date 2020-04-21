#ifndef WINDOW_H_
#define WINDOW_H_

#include <vector>

struct GLFWwindow;
class WindowRenderable;

class Window
{
private:
    GLFWwindow *window;
    std::vector<WindowRenderable*> renderables;
public:
    Window(int width, int height, const char* name);
    ~Window();

    void render();
    void add_system(WindowRenderable *);
    GLFWwindow *getWindow();
};

#endif
