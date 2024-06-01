#include "spsc_buffer.hh"

namespace spsc_buffer {
Buffer::Buffer(uint8_t *buffer) : buffer(buffer), is_full(false) {}

uint8_t *Buffer::write_ptr() {
  if (is_full.load(std::memory_order_acquire)) {
    return nullptr;
  }

  return buffer;
}

void Buffer::commit_write() { is_full.store(true, std::memory_order_release); }

uint8_t *Buffer::read_ptr() {
  if (!is_full.load(std::memory_order_acquire)) {
    return nullptr;
  }

  return buffer;
}

void Buffer::commit_read() { is_full.store(false, std::memory_order_release); }
} // namespace spsc_buffer