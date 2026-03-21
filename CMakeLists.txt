cmake_minimum_required(VERSION 3.26)
project(dsa_nba_generator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(dsa_nba_generator
        classes_and_functions.cpp
        classes_and_functions.h
        max_heap.cpp
        max_heap.h
        son_main.cpp
)
