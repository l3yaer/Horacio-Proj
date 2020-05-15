cmake_minimum_required(VERSION 3.15)

set(CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/core)

add_subdirectory(core)
add_subdirectory(ui)

add_library(proj Core.cpp Core.h)
