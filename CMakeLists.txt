cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 20)

project(libtr_lang)

find_package(libtr_lang REQUIRED)

add_subdirectory(tests)

# Tests
include (../Catch2/contrib/ParseAndAddCatchTests.cmake)
add_subdirectory(../Catch2 catch2)
enable_testing()
