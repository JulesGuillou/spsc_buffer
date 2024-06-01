#include "spsc_buffer.hh"
#include <future>
#include <gtest/gtest.h>

namespace spsc_buffer {
std::atomic<bool> stop_flag{false};

TEST(MT_00, SPSCBuffer) {
  stop_flag.store(false);
  constexpr size_t buffer_size = sizeof(size_t);
  constexpr size_t nb_operations = 100000000;
  auto raw_buffer = std::make_unique<uint8_t[]>(buffer_size);
  auto buffer = Buffer(raw_buffer.get());

  // Lambda function that write nb_operations times to the buffer.
  auto write_task = [&buffer]() {
    for (size_t i = 0; i < nb_operations; i++) {
      uint8_t *write_ptr = buffer.write_ptr();
      while (write_ptr == nullptr) {
        if (stop_flag.load()) {
          return;
        }
        write_ptr = buffer.write_ptr();
      }

      *reinterpret_cast<size_t *>(write_ptr) = i;
      buffer.commit_write();
    }
  };

  // Lambda function that read nb_operations times from the buffer.
  auto read_task = [&buffer]() {
    for (size_t i = 0; i < nb_operations; i++) {
      uint8_t *read_ptr = buffer.read_ptr();
      while (read_ptr == nullptr) {
        if (stop_flag.load()) {
          return;
        }
        read_ptr = buffer.read_ptr();
      }

      size_t value = *reinterpret_cast<size_t *>(read_ptr);
      ASSERT_EQ(value, i);
      buffer.commit_read();
    }
  };

  std::future<void> write_thread = std::async(write_task);
  std::future<void> read_thread = std::async(read_task);

  read_thread.get();
  stop_flag.store(true);
  write_thread.get();
}
} // namespace spsc_buffer