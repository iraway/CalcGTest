include_directories(${CMAKE_SOURCE_DIR})

add_executable(calc_tests
        calculator_test.cpp
        history_test.cpp
)

target_link_libraries(calc_tests
        PRIVATE CalcLib
        PRIVATE gtest
        PRIVATE gmock
        PRIVATE gtest_main
)

add_test(NAME CalcTests COMMAND calc_tests)
