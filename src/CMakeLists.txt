cmake_minimum_required(VERSION 3.15)

add_subdirectory(core)
add_subdirectory(ui)

set(SRC_DIR ${UI_DIR} ${CORE_DIR} PARENT_SCOPE)
