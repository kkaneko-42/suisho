project(suisho_examples)

add_executable(hello_world hello_world/main.cpp)
add_executable(vulkan_tutorial vulkan_tutorial/main.cpp)

target_include_directories(hello_world PRIVATE hello_world/)
target_include_directories(vulkan_tutorial PRIVATE vulkan_tutorial/)

target_compile_features(vulkan_tutorial PRIVATE cxx_std_20)
target_compile_definitions(vulkan_tutorial PRIVATE SUISHO_VK_TUTORIAL_RESOURCES_DIR="${PROJECT_SOURCE_DIR}/vulkan_tutorial/")
target_link_libraries(hello_world PRIVATE suisho_framework)
target_link_libraries(vulkan_tutorial PRIVATE suisho_framework)
