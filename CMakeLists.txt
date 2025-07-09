cmake_minimum_required(VERSION 3.22)
project(CalcGTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CalcLib
        ICalculator.h
        SimpleCalculator.h SimpleCalculator.cpp
        IHistory.h
        InMemoryHistory.h InMemoryHistory.cpp
)
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(tests)