cmake_minimum_required(VERSION 3.11)

project(lib_functions)

set(main_src main)
set(module_src module)

add_library(module SHARED ${module_src})
add_library(main SHARED ${main_src})

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(O_FLAG "-O2")

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE ${O_FLAG})

set_target_properties(
    main
    module
    PROPERTIES SUFFIX ".bc" CXX_STANDARD 11)

add_custom_command(TARGET main
    POST_BUILD
    COMMAND emcc
    -s ALLOW_MEMORY_GROWTH=1
    -s ERROR_ON_UNDEFINED_SYMBOLS=0
    -s EXPORT_ALL=1
    -s MAIN_MODULE=1
    --bind
    ${O_FLAG} libmain.bc
    -o ${CMAKE_CURRENT_SOURCE_DIR}/output/main.js
)

add_custom_command(TARGET module
    POST_BUILD
    COMMAND emcc
    -s EXPORT_ALL=1
    -s SIDE_MODULE=1
    -v
    ${O_FLAG} libmodule.bc
    -o ${CMAKE_CURRENT_SOURCE_DIR}/output/module.wasm
)