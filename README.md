# SPSC Buffer

## Overview

The SPSC (Single-Producer Single-Consumer) Buffer is a high-performance buffer implementation designed for scenarios where a single producer thread writes data and a single consumer thread reads data. This buffer is optimized for low-latency and high-throughput applications, making it suitable for real-time systems such as image processing pipelines.

## Features

- **Single-Producer Single-Consumer:** Optimized for scenarios with one producer and one consumer.
- **Lock-Free:** Utilizes atomic operations for synchronization, avoiding the need for mutexes or other locking mechanisms.
- **High Performance:** Designed for low-latency and high-throughput applications.
- **Memory Efficiency:** Can only contain one element at a time, ensuring efficient memory usage.

## Performance
```sh
Running /home/julesg/Documents/spsc_buffer/build/benchmarks/Release/spsc_buffer_benchmarks
Run on (16 X 2767.03 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 512 KiB (x8)
  L3 Unified 4096 KiB (x2)
Load Average: 1.15, 1.34, 1.14
-----------------------------------------------------------------------------------------------
Benchmark                                     Time             CPU   Iterations UserCounters...
-----------------------------------------------------------------------------------------------
BM_NoMemoryTransfer/min_time:5.000         4.01 ns         4.01 ns   1757555946 Bandwidth=952.307Ti/s Transfers=499.283M/s
BM_WithMemoryTransfer/min_time:5.000     391878 ns       391861 ns        18318 Bandwidth=9.96847Gi/s Transfers=5.10386k/s
```

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Performance](#performance)
- [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Building the Project](#building-the-project)
    - [Running Examples](#running-examples)
    - [Running Tests](#running-tests)
    - [Running Benchmarks](#running-benchmarks)
- [Documentation](#documentation)
- [Usage](#usage)
    - [Minimal Example](#minimal-example)
    - [Other Examples](#other-examples)
- [Contributing](#contributing)
- [License](#license)

## Getting Started

### Prerequisites

- **CMake:** Version 3.10 or higher.
- **C++ Compiler:** GCC, Clang, or MSVC (cl).
- **Doxygen:** For generating documentation.

### Building the Project

1. **Clone the Repository:**
   ```sh
   git clone https://github.com/JulesGuillou/spsc_buffer.git
   cd spsc_buffer
   ```

2. **Configure the Project:**
   ```sh
   cmake -S . -B build
   ```

3. **Build the Project:**
   ```sh
   cmake --build build
   ```

### Running Examples

1. **Build and Run Minimal Example:**
   ```sh
   cmake --build build --target minimal_example
   ./build/examples/minimal_example
   ```

### Running Tests

1. **Build and Run Tests:**
   ```sh
   cmake --build build --target spsc_buffer_tests
   ctest --test-dir build
   ```

### Running Benchmarks

1. **Build and Run Benchmarks:**
   ```sh
   cmake --build build --target spsc_buffer_benchmarks
   ./build/benchmarks/spsc_buffer_benchmarks
   ```

### Generating Documentation

1. **Generate Documentation:**
   ```sh
   cmake --build build --target doc_doxygen
   ```

2. **View Documentation:**
   Open `build/docs/html/index.html` in your web browser.

## Documentation

The project documentation is generated using Doxygen and provides detailed information about the classes, methods, and usage of the SPSC Buffer.

## Usage

### Minimal Example

```cpp
#include "spsc_buffer.hh"
#include <algorithm>
#include <iostream>
#include <memory>

using Buffer = spsc_buffer::Buffer;

int main() {
  // Create the buffer.
  constexpr size_t buffer_size = 8 * 512 * 512;
  auto raw_buffer = std::make_unique<uint8_t[]>(buffer_size);
  auto buffer = Buffer(raw_buffer.get());

  // Write.
  auto write_ptr = buffer.write_ptr();
  std::fill(write_ptr, write_ptr + buffer_size, 0);
  buffer.commit_write();

  // Read.
  auto read_ptr = buffer.read_ptr();
  auto all_zeros = std::all_of(read_ptr, read_ptr + buffer_size,
                               [](uint8_t byte) { return byte == 0; });
  std::cout << "All zeros: " << all_zeros << std::endl;
  buffer.commit_read();
}
```

### Other Examples
Other examples can be found in the `examples` directory.

## Contributing

Contributions are welcome! Please follow these steps to contribute:

1. **Fork the Repository:**
   Click the "Fork" button at the top right of the repository page.

2. **Clone Your Fork:**
   ```sh
   git clone https://github.com/yourusername/spsc_buffer.git
   cd spsc_buffer
   ```

3. **Create a Branch:**
   ```sh
   git checkout -b feature/your-feature-name
   ```

4. **Make Your Changes:**
   Implement your feature or fix.

5. **Commit Your Changes:**
   ```sh
   git add .
   git commit -m "Add your commit message"
   ```

6. **Push to Your Fork:**
   ```sh
   git push origin feature/your-feature-name
   ```

7. **Create a Pull Request:**
   Go to the original repository and click the "New Pull Request" button.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.