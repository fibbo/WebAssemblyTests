cmake_minimum_required(VERSION 3.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)

add_executable(main main.cpp)
add_executable(side side.cpp)

set(CMAKE_CXX_FLAGS "-std=c++11")

set_target_properties(main PROPERTIES LINK_FLAGS 
    "--cache ${CMAKE_SOURCE_DIR}/../emscripten_cache\
    -s MAIN_MODULE=1\
    -s EXPORT_ALL=1\
    -s ALLOW_MEMORY_GROWTH=1\
    -s ASSERTIONS=2\
    -s WARN_ON_UNDEFINED_SYMBOLS=1\
    -s DISABLE_EXCEPTION_CATCHING=0\ 
    -s NO_EXIT_RUNTIME=1\
    -s ERROR_ON_UNDEFINED_SYMBOLS=0\
    -s EXTRA_EXPORTED_RUNTIME_METHODS=\"['stringToUTF8']\"\
    -s FORCE_FILESYSTEM=1\
    -s \"BINARYEN_TRAP_MODE='clamp'\"\ 
    --bind"
)

set_target_properties(side PROPERTIES LINK_FLAGS
  "--cache ${CMAKE_SOURCE_DIR}/../emscripten_cache\
  -s \"BINARYEN_TRAP_MODE='clamp'\"\ 
  -s SIDE_MODULE=1\
  -s ASSERTIONS=1\
  -s EXPORT_ALL=1"
)
