cmake_minimum_required(VERSION 3.15)

add_library(rules
  Fact.cpp
  Value.cpp
  AlphaMemory.cpp
  AlphaMemoryNode.cpp
  AlphaNode.cpp
  SelectionNode.cpp
  TypeNode.cpp
  Tuple.cpp
  BetaMemory.cpp
  BetaMemoryNode.cpp
  TupleFactList.cpp)

target_include_directories(rules PUBLIC ${CORE_DIR})
target_link_libraries(rules PRIVATE core ${CMAKE_DL_LIBS})
set(RULES_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
