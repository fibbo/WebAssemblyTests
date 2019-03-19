cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

set(copy_src copy)

add_library(copy SHARED ${copy_src})

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(O_FLAG "-O2")

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE ${O_FLAG})

set_target_properties(
    copy
    PROPERTIES SUFFIX ".bc" CXX_STANDARD 11)

add_custom_command(TARGET copy
    POST_BUILD
    COMMAND emcc
    -s ALLOW_MEMORY_GROWTH=1
    -s FORCE_FILESYSTEM=1
    --bind
    ${O_FLAG} libcopy.bc
    -o ${CMAKE_CURRENT_SOURCE_DIR}/output/copy.js
)

