cmake_minimum_required(VERSION 3.2)

project(spell-config C CXX)
set(CMAKE_CXX_STANDARD 11)

add_library(spell src/document_node.cpp)
