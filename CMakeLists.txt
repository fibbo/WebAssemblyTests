cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

add_subdirectory(memory bin/memory)
add_subdirectory(copy bin/copy)
add_subdirectory(modules bin/modules)
add_subdirectory(dynamicLibraries bin/dynamicLibraries)
add_subdirectory(dlopen bin/dlopen)
add_subdirectory(loadDynamicLibrary bin/loadDynamicLibrary)


add_custom_target(empty)