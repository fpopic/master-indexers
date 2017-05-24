cmake_minimum_required(VERSION 3.7)
project(thesis_indexers)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -std=c++11 -O3")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

add_executable(indexer indexer.cpp)
