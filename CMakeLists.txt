cmake_minimum_required(VERSION 3.21)
project(NiceFormatPrint)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

add_compile_options(-Wall)

add_subdirectory(execute)
add_subdirectory(tests)
add_subdirectory(lib)


