cmake_minimum_required(VERSION 3.27)
project(spsc_buffer VERSION 0.1)

# Default build type
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif ()

option(SPSC_BUFFER_ENABLE_TESTING "Build tests" ON)

if (SPSC_BUFFER_ENABLE_TESTING)
    enable_testing()
endif ()

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)
add_subdirectory(benchmarks)
add_subdirectory(docs)
