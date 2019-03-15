cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

add_library(main SHARED main)
add_library(side_module SHARED module)


set_target_properties(
    main
    side_module
    PROPERTIES SUFFIX ".bc" CXX_STANDARD 11)

add_custom_command(TARGET main
    POST_BUILD
    COMMAND emcc
    -s ALLOW_MEMORY_GROWTH=1
    -s MAIN_MODULE=1
    -s EXPORT_ALL=1 # without this other modules cannot allocate memory
    --embed-file ${CMAKE_SOURCE_DIR}/output/side_module.wasm@/usr/lib/side_module.wasm
    --pre-js ${CMAKE_SOURCE_DIR}/pre.js
    --bind
    -O2 libmain.bc
    -o ${CMAKE_CURRENT_SOURCE_DIR}/output/main.js
)

add_custom_command(TARGET side_module
    POST_BUILD
    COMMAND emcc
    -s SIDE_MODULE=1
    # -s EXPORTED_FUNCTIONS="['_fillDataStructure']"
    -s EXPORT_ALL=1
    libside_module.bc
    -o ${CMAKE_CURRENT_SOURCE_DIR}/output/side_module.wasm
)
