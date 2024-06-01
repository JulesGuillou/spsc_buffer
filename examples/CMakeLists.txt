# Minimal example
add_executable(minimal_example minimal_example.cc)

set_target_properties(minimal_example PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_compile_options(minimal_example PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

target_link_libraries(minimal_example PRIVATE
        spsc_buffer
)
