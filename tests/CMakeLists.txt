add_executable(spsc_buffer_tests
        multithread_tests.cc
)

set_target_properties(spsc_buffer_tests PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_compile_options(spsc_buffer_tests PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

target_link_libraries(spsc_buffer_tests PRIVATE
        gtest_main
        spsc_buffer
)

include(GoogleTest)
gtest_discover_tests(spsc_buffer_tests)
