cmake_minimum_required (VERSION 2.6)

project(log LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(logger)

add_library(log SHARED src/main.cpp)
target_link_libraries(log PUBLIC logger)
