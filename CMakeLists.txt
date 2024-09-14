cmake_minimum_required(VERSION 3.11)
project(suisho)

option(SUISHO_BUILD_EXAMPLE "Build the examples" ON)

add_subdirectory(./framework)

if (SUISHO_BUILD_EXAMPLE)
    add_subdirectory(./examples)
endif()
