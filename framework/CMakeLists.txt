cmake_minimum_required(VERSION 3.11)
project(suisho_framework CXX)

find_package(Vulkan REQUIRED)

# Fetch dependencies
include(FetchContent)

FetchContent_Declare(
    entt
    GIT_REPOSITORY https://github.com/skypjack/entt
    GIT_TAG v3.13.2
)

set(BUILD_SHARED_LIBS ON)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 3.4
)

FetchContent_MakeAvailable(entt glfw)

# Gather engine sources
include(core/CMakeLists.txt)
include(math/CMakeLists.txt)
include(rendering/CMakeLists.txt)
set(SUISHO_FRAMEWORK_SRCS
    ${SUISHO_CORE_SRCS}
    ${SUISHO_MATH_SRCS}
    ${SUISHO_RENDERING_SRCS}
)

add_library(suisho_framework STATIC ${SUISHO_FRAMEWORK_SRCS})

target_include_directories(suisho_framework PUBLIC ./)
target_include_directories(suisho_framework PUBLIC ${entt_SOURCE_DIR}/src)
target_include_directories(suisho_framework PUBLIC ${glfw_SOURCE_DIR}/include)

target_link_libraries(suisho_framework INTERFACE EnTT glfw)
