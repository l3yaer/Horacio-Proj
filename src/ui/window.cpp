#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "window.h"
#include "windowRenderable.h"

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

Window::Window(int width, int height, const char* name)
{
   glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        return;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#ifdef GLFW_COCOA_RETINA_FRAMEBUFFER
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_TRUE);
#endif
#ifdef GLFW_COCOA_GRAPHICS_SWITCHING
    glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, GL_TRUE);
#endif
#endif
    window = glfwCreateWindow(width, height, name, NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    gl3wInit();
}

Window::~Window()
{
    renderables.clear();
    glfwTerminate();
}

void Window::render()
{
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        for(auto &renderable: renderables)
            renderable->update();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.125f, 0.125f, 0.125f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        for(auto &renderable: renderables)
            renderable->render();

        glfwSwapBuffers(window);
    }
}

void Window::add_system(WindowRenderable *renderable)
{
    renderables.push_back(renderable);
}

GLFWwindow* Window::getWindow()
{
    return window;
}
