cmake_minimum_required(VERSION 3.15)
project(Horacio-Proj)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

add_subdirectory(thirdParty)
add_subdirectory(src)

add_executable(Horacio-Proj main.cpp)
target_link_libraries(Horacio-Proj proj ui)
target_include_directories(Horacio-Proj PUBLIC ${SRC_DIR})
