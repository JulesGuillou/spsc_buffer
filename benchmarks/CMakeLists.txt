add_executable(spsc_buffer_benchmarks benchmarks.cc)

set_target_properties(spsc_buffer_benchmarks PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_compile_options(spsc_buffer_benchmarks PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

target_link_libraries(spsc_buffer_benchmarks PRIVATE
        benchmark::benchmark
        spsc_buffer
)
