cmake_minimum_required(VERSION 3.11)
project(suisho_framework CXX)
set(SUISHO_FRAMEWORK_NAME suisho_framework)

include(FetchContent)

set(BUILD_SHARED_LIBS ON)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
FetchContent_Declare(
    entt
    GIT_REPOSITORY https://github.com/skypjack/entt
    GIT_TAG v3.13.2
)
FetchContent_MakeAvailable(entt)

include(core/CMakeLists.txt)
include(math/CMakeLists.txt)
include(rendering/CMakeLists.txt)
set(SUISHO_FRAMEWORK_SRCS
    ${SUISHO_CORE_SRCS}
    ${SUISHO_MATH_SRCS}
    ${SUISHO_RENDERING_SRCS}
)

add_library(${SUISHO_FRAMEWORK_NAME} STATIC ${SUISHO_FRAMEWORK_SRCS})

target_include_directories(${SUISHO_FRAMEWORK_NAME} PUBLIC ./)
target_include_directories(${SUISHO_FRAMEWORK_NAME} PUBLIC ${entt_SOURCE_DIR}/src)

target_link_libraries(${SUISHO_FRAMEWORK_NAME} INTERFACE EnTT)
