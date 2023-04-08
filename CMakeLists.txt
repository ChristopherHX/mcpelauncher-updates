cmake_minimum_required (VERSION 2.6)

project(log LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(jnivmsupport SHARED src/main.cpp)
target_include_directories(jnivmsupport libjnivm/include)