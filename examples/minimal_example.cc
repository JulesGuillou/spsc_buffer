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