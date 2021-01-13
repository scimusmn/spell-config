cmake_minimum_required(VERSION 3.2)

project(spell-config C CXX)
set(CMAKE_CXX_STANDARD 11)

add_library(spell src/document_node.cpp)

add_executable(demo demo/main.cpp)
set_target_properties(demo PROPERTIES EXCLUDE_FROM_ALL TRUE)
link_directories(${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(demo spell)
