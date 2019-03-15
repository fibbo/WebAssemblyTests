cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

set(main_src main)
set(module_src module)
set(module2_src module2)
set(dynamic_src dynamic)

add_library(main SHARED ${main_src})
add_library(side_module SHARED ${module_src})
add_library(side_module2 SHARED ${module2_src})
add_library(dynamic SHARED ${dynamic_src})
set_target_properties(
    main
    side_module
    side_module2
    dynamic
    PROPERTIES SUFFIX ".bc" CXX_STANDARD 11)

add_custom_command(TARGET main
    POST_BUILD
    COMMAND emcc
    -s ALLOW_MEMORY_GROWTH=1
    -s ERROR_ON_UNDEFINED_SYMBOLS=0
    -s MAIN_MODULE=1
    -s EXPORT_ALL=1
    --bind
    -O2 libmain.bc
    -o ${CMAKE_CURRENT_SOURCE_DIR}/output/main.js
)

add_custom_command(TARGET side_module
    POST_BUILD
    COMMAND emcc
    -s SIDE_MODULE=1
    -s EXPORT_ALL=1
    -O2 libside_module.bc
    -o ${CMAKE_CURRENT_SOURCE_DIR}/output/side_module.wasm
)

add_custom_command(TARGET side_module2
    POST_BUILD
    COMMAND emcc
    -s SIDE_MODULE=1
    -s EXPORT_ALL=1
    -O2 libside_module2.bc
    -o ${CMAKE_CURRENT_SOURCE_DIR}/output/side_module2.wasm
)

add_custom_command(TARGET dynamic
    POST_BUILD
    COMMAND emcc
    -s SIDE_MODULE=1
    -s EXPORT_ALL=1
    -O2 libdynamic.bc
    -o ${CMAKE_CURRENT_SOURCE_DIR}/output/dynamic.wasm
)
