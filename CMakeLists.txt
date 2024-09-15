cmake_minimum_required(VERSION 3.11)
project(suisho)

option(SUISHO_BUILD_EXAMPLES "Build the examples" ON)
option(SUISHO_BUILD_TESTS "Build the tests" ON)

add_subdirectory(./framework)

if (SUISHO_BUILD_EXAMPLES)
    add_subdirectory(./examples)
endif()

if (SUISHO_BUILD_TESTS)
    add_subdirectory(./tests)
endif()
