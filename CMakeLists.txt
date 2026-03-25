cmake_minimum_required(VERSION 3.26)
project(dsa_nba_generator)
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(.)
add_executable(dsa_nba_generator
        classes_and_functions.cpp
        classes_and_functions.h
        max_heap.cpp
        max_heap.h
        max_heap.cpp
        SplayTree.cpp
        jovon_main.cpp
)
target_link_libraries(dsa_nba_generator sfml-graphics sfml-window sfml-system)
add_custom_command(TARGET dsa_nba_generator POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:dsa_nba_generator>
        $<TARGET_FILE_DIR:dsa_nba_generator>
        COMMAND_EXPAND_LISTS
)