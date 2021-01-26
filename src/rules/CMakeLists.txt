cmake_minimum_required(VERSION 3.15)

add_library(rules
  Value.cpp
  Triple.cpp
  AlphaNode.cpp
  ReteNode.cpp
  Condition.cpp
  TestNode.cpp
  BetaNode.cpp
  DummyNode.cpp
  JoinNode.cpp
  ProductionNode.cpp
  TokenFilterNode.cpp
  ReteNet.cpp)

target_include_directories(rules PUBLIC ${CORE_DIR})
target_link_libraries(rules PRIVATE core ${CMAKE_DL_LIBS})
set(RULES_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
