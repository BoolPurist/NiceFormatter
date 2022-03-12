add_executable(execution main.cpp includer_tester.cpp)

set(CMAKE_CXX_STANDARD 17)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

message(STATUS ${CMAKE_CXX_FLAGS})

target_link_libraries(execution PRIVATE NiceFormatPrint)