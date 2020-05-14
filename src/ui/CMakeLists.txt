cmake_minimum_required(VERSION 3.15)

find_package(OpenGL REQUIRED)

if (WIN32)
    find_package(SDL2 REQUIRED)
    find_package(SDL2IMAGE REQUIRED)
else ()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
endif ()

add_library(ui
        WindowManager.cpp
        imgui/ImguiWindow.cpp
        imgui/imgui_impl_sdl.cpp
        imgui/imgui_impl_opengl3.cpp
        Filesystem.cpp
        Loader.cpp
        MapManager.cpp
        Program.cpp
        Square.cpp
        Texture.cpp
        TextureFactory.cpp
        Tile.cpp
        TileFactory.cpp
        Movable.cpp Renderable.cpp Renderable.h Mesh.cpp Mesh.h Singleton.h Shaders.cpp Shaders.h Camera.cpp Camera.h JobManager.cpp JobManager.h)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

target_include_directories(ui PRIVATE ${OPENGL_INCLUDE_DIR})

target_compile_definitions(ui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

target_link_libraries(ui PRIVATE ${OPENGL_gl_LIBRARY} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} glad imgui glm curl taskScheduler ${CMAKE_DL_LIBS})
