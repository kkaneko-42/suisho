# TODO: cmake_minimum_required
project(suisho_framework CXX)
set(SUISHO_FRAMEWORK_NAME suisho_framework)

include(core/CMakeLists.txt)
include(math/CMakeLists.txt)
include(rendering/CMakeLists.txt)
set(SUISHO_FRAMEWORK_SRCS
    ${SUISHO_CORE_SRCS}
    ${SUISHO_MATH_SRCS}
    ${SUISHO_RENDERING_SRCS}
)

add_library(${SUISHO_FRAMEWORK_NAME} STATIC ${SUISHO_FRAMEWORK_SRCS})

target_include_directories(${SUISHO_FRAMEWORK_NAME} PUBLIC framework/)
