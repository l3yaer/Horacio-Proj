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
        MapManager.cpp
        Program.cpp
        Square.cpp
        Texture.cpp
        TextureManager.cpp
        Tile.cpp
        TileFactory.cpp
        Shaders.cpp
        constants.h
        debug/Square.cpp
        GuiActor.cpp
        ProgramManager.cpp
        GuiMap.cpp
        Renderer.cpp
		MeshManager.cpp
        )
	  
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

target_include_directories(ui PRIVATE ${OPENGL_INCLUDE_DIR})

target_include_directories(ui PUBLIC ${CORE_DIR})

target_compile_definitions(ui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

target_link_libraries(ui ${OPENGL_gl_LIBRARY} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} glad imgui glm curl core ${CMAKE_DL_LIBS})

set(UI_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
