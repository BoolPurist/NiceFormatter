cmake_minimum_required(VERSION 3.21)
project(NiceFormatPrint)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(execute)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

set(SOURCE_FILES Format.cpp PlaceholderPosition.cpp  FormatPrinter.cpp)
set(HEADER_FILES Format.h PlaceholderPosition.h FormatPrinter.h Token.h)
set(TEMPLATE_FILES Format.tpp FormatPrinter.tpp)

add_library(NiceFormatPrint ${SOURCE_FILES} ${HEADER_FILES} ${TEMPLATE_FILES})
