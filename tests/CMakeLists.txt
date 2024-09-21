project(suisho_test CXX)

include(FetchContent)

FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(gtest)

include(core/CMakeLists.txt)
include(math/CMakeLists.txt)

function(configure_test bin srcs)
    add_executable(${bin} ${srcs})
    target_include_directories(${bin} PRIVATE ${gtest_SOURCE_DIR}/googletest/include)
    target_link_directories(${bin} PRIVATE ${gtest_BINARY_DIR})
    target_link_libraries(${bin} PRIVATE suisho_framework gtest gtest_main)
endfunction(configure_test)

configure_test(core_test "${SUISHO_TEST_CORE_SRCS}")
configure_test(math_test "${SUISHO_TEST_MATH_SRCS}")
