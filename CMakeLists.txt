cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)

project(libtr_lang)

find_package(libtr_lang REQUIRED)

add_subdirectory(tests)