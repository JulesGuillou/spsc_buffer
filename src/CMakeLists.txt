add_library(spsc_buffer STATIC
        spsc_buffer.cc
)

set_target_properties(spsc_buffer PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_compile_options(spsc_buffer PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

target_include_directories(spsc_buffer PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
