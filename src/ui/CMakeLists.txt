cmake_minimum_required(VERSION 3.15)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_library(fsm-ui window.cpp imguiWindow.cpp nuklearWindow.cpp imgui_impl_glfw_gl3.cpp)

target_compile_definitions(fsm-ui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GL3W)

target_include_directories(fsm-ui PRIVATE ${OPENGL_INCLUDE_DIR})

target_link_libraries(fsm-ui PRIVATE ${OPENGL_gl_LIBRARY} gl3w glfw imgui nuklear)
