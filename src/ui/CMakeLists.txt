cmake_minimum_required(VERSION 3.15)

find_package(OpenGL REQUIRED)

if(WIN32)
  find_package(SDL2 REQUIRED)
else()
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(SDL2 REQUIRED sdl2)
endif()

add_library(fsm-ui
  window.cpp
  imgui/window.cpp
  imgui/imgui_impl_sdl.cpp
  imgui/imgui_impl_opengl3.cpp)

include_directories(${SDL2_INCLUDE_DIRS})

target_include_directories(fsm-ui PRIVATE ${OPENGL_INCLUDE_DIR})

target_compile_definitions(fsm-ui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

target_link_libraries(fsm-ui PRIVATE ${OPENGL_gl_LIBRARY} ${SDL2_LIBRARIES} glad imgui ${CMAKE_DL_LIBS})
