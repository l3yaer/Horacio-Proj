cmake_minimum_required(VERSION 3.15)

add_subdirectory(core)
add_subdirectory(ui)
add_subdirectory(rules)
add_subdirectory(map)

set(SRC_DIR ${UI_DIR} ${CORE_DIR} ${RULES_DIR} ${MAP_DIR} PARENT_SCOPE)
