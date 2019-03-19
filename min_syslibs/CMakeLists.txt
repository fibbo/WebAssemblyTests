cmake_minimum_required(VERSION 3.11)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(O_FLAG "-O0")

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE ${O_FLAG})

add_library(main SHARED main)
add_library(module SHARED module)


set_target_properties(
    main
    module
    PROPERTIES SUFFIX ".bc" CXX_STANDARD 11)

add_custom_command(TARGET main
    POST_BUILD
    COMMAND set \"EMCC_FORCE_STDLIBS=1\"
    COMMAND emcc
    -s MAIN_MODULE=1
    -s EXPORT_ALL=1
    --bind
    ${O_FLAG} libmain.bc
    -o ${CMAKE_CURRENT_SOURCE_DIR}/output/main.js
)

add_custom_command(TARGET module
    POST_BUILD
    COMMAND set \"EMCC_FORCE_STDLIBS=0\"
    COMMAND emcc
    -v
    -s EXPORT_ALL=1
    -s SIDE_MODULE=1
    ${O_FLAG} libmodule.bc
    -o ${CMAKE_CURRENT_SOURCE_DIR}/output/module.wasm
)