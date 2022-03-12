cmake_minimum_required(VERSION 3.21)
project(NiceFormatPrint)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(execute)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_library(NiceFormatPrint Format.cpp Format.h Token.h PlaceholderPosition.cpp PlaceholderPosition.h FormatPrinter.cpp FormatPrinter.h)
