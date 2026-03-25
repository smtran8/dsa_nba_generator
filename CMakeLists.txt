cmake_minimum_required(VERSION 4.0)
project(dsa_nba_generator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(dsa_nba_generator
        classes_and_functions.h
        splayTree.cpp
        SplayTree.cpp
)
