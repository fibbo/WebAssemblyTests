cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

set(main_src main)
set(module_src module)
set(module2_src module2)

add_library(main SHARED ${main_src})
add_library(side_module SHARED ${module_src})
add_library(side_module2 SHARED ${module2_src})

set_target_properties(
    main
    side_module
    side_module2
    PROPERTIES SUFFIX ".bc" CXX_STANDARD 11)

add_custom_command(TARGET main
    POST_BUILD
    COMMAND emcc
    -s ALLOW_MEMORY_GROWTH=1
    -s ERROR_ON_UNDEFINED_SYMBOLS=0
    -s MAIN_MODULE=1
    -s EXPORT_ALL=1
    --embed-file ${CMAKE_SOURCE_DIR}/bin/side_module.wasm@/usr/lib/side_module.wasm
    --pre-js ${CMAKE_SOURCE_DIR}/pre.js
    --bind
    libmain.bc
    -o ${CMAKE_CURRENT_SOURCE_DIR}/bin/main.js
)

add_custom_command(TARGET side_module
    POST_BUILD
    COMMAND emcc
    -s SIDE_MODULE=1
    -s EXPORT_ALL=1
    libside_module.bc
    -o ${CMAKE_CURRENT_SOURCE_DIR}/bin/side_module.wasm
)

add_custom_command(TARGET side_module2
    POST_BUILD
    COMMAND emcc
    -s SIDE_MODULE=1
    -s EXPORT_ALL=1
    libside_module2.bc
    -o ${CMAKE_CURRENT_SOURCE_DIR}/bin/side_module2.wasm
)

