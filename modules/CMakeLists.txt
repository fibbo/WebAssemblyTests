cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

set(main_src main)
set(module_src module)

add_library(main SHARED ${main_src})
add_library(side_module SHARED ${module_src})

set_target_properties(
    main
    side_module
    PROPERTIES SUFFIX ".bc" CXX_STANDARD 11)

add_custom_command(TARGET main
    POST_BUILD
    COMMAND emcc
    -s ALLOW_MEMORY_GROWTH=1
    -s FORCE_FILESYSTEM=1
    -s EXPORT_ALL=1
    --bind
    -O2 libmain.bc
    -o ${CMAKE_CURRENT_SOURCE_DIR}/bin/main.js
)

add_custom_command(TARGET side_module
    POST_BUILD
    COMMAND emcc
    -s SIDE_MODULE=1
    -s EXPORT_ALL=1
    --bind
    libmodule.bc
    -o ${CMAKE_CURRENT_SOURCE_DIR}/bin/side_module.wasm
)

