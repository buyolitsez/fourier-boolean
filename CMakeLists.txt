cmake_minimum_required(VERSION 3.27)
project(mod3)

set(CMAKE_CXX_STANDARD 23)

add_executable(mod3 main.cpp
        fourier.hpp
        check_xor_dnf.h)
