cmake_minimum_required(VERSION 3.12)

project(emscripten_fetch)

set(src fetch_api.cpp)

set(CMAKE_CXX_FLAGS "-std=c++11 --bind -s FETCH=1 -s ENVIRONMENT=worker -s ALLOW_MEMORY_GROWTH=1")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(emscripten_fetch ${src})

