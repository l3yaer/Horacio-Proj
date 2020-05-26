cmake_minimum_required(VERSION 3.15)

add_library(core
        World.cpp
        Movable.cpp
        Camera.cpp
        World.cpp
        JobManager.cpp
        Filesystem.cpp ResourceManager.cpp ResourceManager.h Resource.cpp Resource.h Actor.cpp Actor.h)

target_link_libraries(core PRIVATE glm curl taskScheduler ${CMAKE_DL_LIBS})
set(CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)