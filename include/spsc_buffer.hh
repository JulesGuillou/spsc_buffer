#pragma once

#include <atomic>
#include <cstdint>

namespace spsc_buffer {

/**
 * @class Buffer
 * @brief A lock-free, single-producer single-consumer (SPSC) buffer.
 *
 * This class implements a buffer that allows a single producer and a single
 * consumer to communicate efficiently. It is designed for high throughput and
 * low latency, making it suitable for real-time applications such as image
 * processing where the buffer can be considered as a tensor for input/output
 * operations between functions running on separate threads.
 *
 * The buffer can only contain one element at a time, and it uses atomic
 * operations for synchronization, avoiding the need for mutexes or other
 * locking mechanisms. This ensures that the buffer is lock-free and provides a
 * high level of performance.
 *
 * @note This buffer is not a queue; it can only hold one element at a time.
 *
 * @example examples/minimal_example.cc
 * An example usage of the Buffer class.
 */
class Buffer {
public:
  /**
   * @brief Constructs a Buffer object.
   *
   * @param buffer A pointer to the memory block that will be used as the
   * buffer.
   */
  explicit Buffer(uint8_t *buffer);

  /**
   * @brief Gets a pointer to the buffer for writing.
   *
   * This function returns a pointer to the buffer where the producer can write
   * data. If the buffer is full, it returns nullptr.
   *
   * @return A pointer to the buffer if it is not full, otherwise nullptr.
   *
   * @note The pointer returned by this function is invalidated after calling
   * commit_write().
   */
  uint8_t *write_ptr();

  /**
   * @brief Commits the write operation.
   *
   * This function marks the buffer as full, indicating that the data has been
   * written and is ready to be read by the consumer.
   *
   * @note This function invalidates the pointer returned by write_ptr().
   */
  void commit_write();

  /**
   * @brief Gets a pointer to the buffer for reading.
   *
   * This function returns a pointer to the buffer where the consumer can read
   * data. If the buffer is empty, it returns nullptr.
   *
   * @return A pointer to the buffer if it is full, otherwise nullptr.
   *
   * @note The pointer returned by this function is invalidated after calling
   * commit_read().
   */
  uint8_t *read_ptr();

  /**
   * @brief Commits the read operation.
   *
   * This function marks the buffer as empty, indicating that the data has been
   * read and the buffer is ready to be written to by the producer.
   *
   * @note This function invalidates the pointer returned by read_ptr().
   */
  void commit_read();

private:
  uint8_t *buffer; ///< Pointer to the memory block used as the buffer.
  std::atomic<bool>
      is_full; ///< Atomic flag indicating whether the buffer is full.
};

} // namespace spsc_buffer
