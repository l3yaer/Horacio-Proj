cmake_minimum_required(VERSION 3.15)
project(FSM-Manager LANGUAGES  C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(thirdParty)
add_subdirectory(src)

add_executable(FSM-Manager main.c)
target_link_libraries(FSM-Manager fsm)
