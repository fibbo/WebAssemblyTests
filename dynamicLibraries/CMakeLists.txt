cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)

set(main_src main)
set(module_src module)
set(module2_src module2)

add_executable(main ${main_src})
add_executable(side_module ${module_src})
add_executable(side_module2 ${module2_src})
set_target_properties(side_module side_module2 PROPERTIES SUFFIX ".wasm")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

set_target_properties(main PROPERTIES LINK_FLAGS
    "-s ALLOW_MEMORY_GROWTH=1\
    -s ERROR_ON_UNDEFINED_SYMBOLS=0\
    -s MAIN_MODULE=1\
    -s EXPORT_ALL=1\
    -g4\
    --source-map-base http://tofino/pgl/WebassemblyTests/dynamicLibraries/output/\
    --bind"
)

set_target_properties(side_module PROPERTIES LINK_FLAGS
    "-s SIDE_MODULE=1\
    -g4\
    --source-map-base http://tofino/pgl/WebassemblyTests/dynamicLibraries/output/\
    -s EXPORT_ALL=1"
)

set_target_properties(side_module2 PROPERTIES LINK_FLAGS
    "-s SIDE_MODULE=1\
    -g4\
    --source-map-base http://tofino/pgl/WebassemblyTests/dynamicLibraries/output/\
    -s EXPORT_ALL=1"
)
