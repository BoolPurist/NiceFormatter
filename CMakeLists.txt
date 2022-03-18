cmake_minimum_required(VERSION 3.21)
project(NiceFormatPrint)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

add_compile_options(-Wall)

option(PROJECTS_TESTS "Builds the unit tests" OFF)
option(PROJECTS_CONSOLE "Builds main for playing around" OFF)

if(PROJECTS_TESTS)
    add_subdirectory(tests)
endif()
if(PROJECTS_CONSOLE)
    add_subdirectory(execute)
endif()


add_subdirectory(lib)


