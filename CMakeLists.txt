cmake_minimum_required(VERSION 3.26)
project(dsa_nba_generator)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(dsa_nba_generator
        classes_and_functions.cpp
        max_heap.cpp
        son_main.cpp
)

target_link_libraries(dsa_nba_generator sfml-graphics sfml-window sfml-system)