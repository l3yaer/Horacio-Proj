cmake_minimum_required(VERSION 3.15)

find_package(OpenGL REQUIRED)
 if(WIN32)
  find_package(SDL2 CONFIG REQUIRED)
  find_package(sdl2-image CONFIG REQUIRED)
 else()
 find_package(SDL2 REQUIRED)
 find_package(SDL2_image REQUIRED)
 endif()
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
		RegularPolygon.cpp
		VectorArea.cpp
		NodeRendererVisitor.cpp
		NodeCoordinateAdapterVisitor.cpp
		SphericalMercator.cpp
        )
        
if(NOT WIN32)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_LIBRARY})
endif()

target_include_directories(ui PRIVATE ${OPENGL_INCLUDE_DIR})

target_include_directories(ui PUBLIC ${CORE_DIR})

target_compile_definitions(ui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

if(WIN32)
target_link_libraries(ui ${OPENGL_gl_LIBRARY} SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_image glad imgui glm core ${CMAKE_DL_LIBS})
else()
target_link_libraries(ui ${OPENGL_gl_LIBRARY} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} glad imgui glm core ${CMAKE_DL_LIBS})
endif()

set(UI_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
