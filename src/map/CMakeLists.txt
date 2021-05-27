cmake_minimum_required(VERSION 3.15)

find_package(OpenGL REQUIRED)

add_library(map
       Parser.cpp
        )

target_include_directories(map PRIVATE ${OPENGL_INCLUDE_DIR})

target_link_libraries(map ${OPENGL_gl_LIBRARY}   ${CMAKE_DL_LIBS})

set(MAP_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
