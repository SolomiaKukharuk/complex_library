cmake_minimum_required(VERSION 3.29)
project(complex C)

set(CMAKE_C_STANDARD 11)

include_directories("C  realisation")

add_executable(complex
    "C  realisation/Complex.c"
    "C  realisation/Complex.h"
    "C  realisation/Complex_tests.c"
        "C++ realisation/Complex.cpp")
