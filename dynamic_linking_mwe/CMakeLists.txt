
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)

set(main_src main_api main_api_js)
set(side_src side_api)

add_executable(main ${main_src})
add_executable(side_module ${side_src})
set_target_properties(side_module PROPERTIES SUFFIX ".wasm")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11")

set_target_properties(main PROPERTIES LINK_FLAGS
    "-s ALLOW_MEMORY_GROWTH=1\
    -s ASSERTIONS=2\
    -s ERROR_ON_UNDEFINED_SYMBOLS=0\
    -s MAIN_MODULE=1\
    -s EXPORT_ALL=1\
    --bind"
)

set_target_properties(side_module PROPERTIES LINK_FLAGS
    "-s SIDE_MODULE=1\
    -s ASSERTIONS=2\
    -s EXPORT_ALL=1"
)

