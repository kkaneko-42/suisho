add_executable(hello_world hello_world/main.cpp)

target_include_directories(hello_world PRIVATE hello_world/)

target_compile_features(hello_world PRIVATE cxx_std_20)
target_link_libraries(hello_world PRIVATE suisho_framework)
