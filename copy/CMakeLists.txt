cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

set(copy_src copy)

add_library(copy SHARED ${copy_src})

set_target_properties(
    copy
    PROPERTIES SUFFIX ".bc" CXX_STANDARD 11)

add_custom_command(TARGET copy
    POST_BUILD
    COMMAND emcc
    -s ALLOW_MEMORY_GROWTH=1
    -s FORCE_FILESYSTEM=1
    --bind
    -O2 libcopy.bc
    -o ${CMAKE_CURRENT_SOURCE_DIR}/bin/copy.js
)

