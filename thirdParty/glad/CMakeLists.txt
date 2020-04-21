
set(_glad_Sources src/glad.c)

source_group("" FILES ${_glad_Sources})
add_library(glad STATIC ${_glad_Sources})
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)