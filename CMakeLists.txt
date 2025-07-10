cmake_minimum_required(VERSION 3.27)
project(mod3)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
#
#set(CMAKE_CXX_FLAGS "-Wfloat-equal -Wlogical-op -Wall -Wextra -Wno-unused-result -Wshadow -D_GLIBCXX_DEBUG -fsanitize=address -fsanitize=undefined -fstack-protector-strong -fstack-check -fno-sanitize-recover=all")

set(CMAKE_CXX_STANDARD 23)

add_executable(mod3 main.cpp
        fourier.hpp
        check_xor_dnf.h
        check_all_functions.h)
