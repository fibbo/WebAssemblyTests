cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

add_subdirectory(memory bin/memory)
add_subdirectory(copy bin/copy)
add_subdirectory(modules bin/modules)
add_subdirectory(modules_advanced bin/modules_advanced)
add_subdirectory(modules_dlopen bin/modules_dlopen)
add_subdirectory(modules_loadDynamicLibrary bin/modules_loadDynamicLibrary)


add_custom_target(empty)