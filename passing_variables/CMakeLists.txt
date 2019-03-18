cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

set (refvsvalue_src refvsvalue_test)
set(datastruct_src datastruct)

add_library(refvsvalue SHARED ${refvsvalue_src})
add_library(datastruct SHARED ${datastruct_src})

set_target_properties(
    refvsvalue
    datastruct
    PROPERTIES SUFFIX ".bc" CXX_STANDARD 11)

add_custom_command(TARGET refvsvalue
    POST_BUILD
    COMMAND emcc
    -s ALLOW_MEMORY_GROWTH=1
    --bind
    -s WASM=1
    librefvsvalue.bc
    -o ${CMAKE_CURRENT_SOURCE_DIR}/output/refvsvalue.js
)

add_custom_command(TARGET datastruct
    POST_BUILD
    COMMAND emcc
    -s SIDE_MODULE=1
    -s EXPORTED_FUNCTIONS="['_updateRefDataStruct', '_updateNoRefDataStruct']"
    libdatastruct.bc
    -o ${CMAKE_CURRENT_SOURCE_DIR}/output/datastruct.wasm
    )
