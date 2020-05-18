cmake_minimum_required(VERSION 3.15)

add_subdirectory(core)
add_subdirectory(ui)

add_library(proj Core.cpp Core.h)
set(SRC_DIR ${UI_DIR} ${CORE_DIR} PARENT_SCOPE)