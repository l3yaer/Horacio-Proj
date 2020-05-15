cmake_minimum_required(VERSION 3.15)

add_library(core
        World.cpp
        Movable.cpp)

target_link_libraries(core PRIVATE glm curl taskScheduler ${CMAKE_DL_LIBS})