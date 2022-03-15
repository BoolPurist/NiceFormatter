include(FetchCatchFromGit)

add_executable(unit_tests test-main.cpp test-format-number.cpp test-invalid.cpp)

target_link_libraries(unit_tests PRIVATE
        Catch2::Catch2
        NiceFormatPrint
        )