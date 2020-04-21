cmake_minimum_required(VERSION 3.15)
project(FSM-Manager)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(thirdParty)
add_subdirectory(src)

add_executable(FSM-Manager main.cpp)
target_link_libraries(FSM-Manager fsm fsm-ui)
