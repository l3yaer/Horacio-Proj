cmake_minimum_required(VERSION 3.15)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

add_library(fsm-ui window.cpp nuklearWindow.cpp)

include_directories(${SDL2_INCLUDE_DIRS})

target_include_directories(fsm-ui PRIVATE ${OPENGL_INCLUDE_DIR})

target_link_libraries(fsm-ui PRIVATE ${OPENGL_gl_LIBRARY} ${SDL2_LIBRARIES} glad nuklear)