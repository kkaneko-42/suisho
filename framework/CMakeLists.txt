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

FetchContent_Declare(
    freetype
    GIT_REPOSITORY https://gitlab.freedesktop.org/freetype/freetype
    GIT_TAG VER-2-13-3
)

# FIXME
if (WIN32)
	FetchContent_Declare(
		glfw
		GIT_REPOSITORY https://github.com/glfw/glfw
		GIT_TAG 3.4
	)
	FetchContent_MakeAvailable(entt freetype glfw)
else()
	FetchContent_MakeAvailable(entt freetype)
endif (WIN32)

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

target_compile_features(suisho_framework PUBLIC cxx_std_17)
target_compile_definitions(suisho_framework PUBLIC SUISHO_BUILTIN_ASSETS_DIR="${PROJECT_SOURCE_DIR}/assets/")
target_include_directories(suisho_framework PUBLIC ./)
target_include_directories(suisho_framework PUBLIC ${Vulkan_INCLUDE_DIR})
target_include_directories(suisho_framework PUBLIC ${entt_SOURCE_DIR}/src)
target_include_directories(suisho_framework PUBLIC ${freetype_SOURCE_DIR}/include)
target_include_directories(suisho_framework PUBLIC ${glfw_SOURCE_DIR}/include)

target_link_libraries(suisho_framework INTERFACE Vulkan::Vulkan glfw EnTT freetype)
