#include "spsc_buffer.hh"
#include <benchmark/benchmark.h>
#include <cstring>
#include <memory>

using Buffer = spsc_buffer::Buffer;

static void BM_NoMemoryTransfer(benchmark::State &state) {
  constexpr size_t buffer_size = 8 * 512 * 512;
  auto raw_buffer = std::make_unique<uint8_t[]>(buffer_size);
  auto buffer = Buffer(raw_buffer.get());

  for (auto _ : state) {
    buffer.write_ptr();
    buffer.commit_write();

    buffer.read_ptr();
    buffer.commit_read();
  }

  state.counters["Transfers"] = benchmark::Counter(
      static_cast<double>(state.iterations() * 2), benchmark::Counter::kIsRate);

  state.counters["Bandwidth"] = benchmark::Counter(
      static_cast<double>(state.iterations() * 2) * 8 * 512 * 512,
      benchmark::Counter::kIsRate, benchmark::Counter::kIs1024);
}

static void BM_WithMemoryTransfer(benchmark::State &state) {
  constexpr size_t buffer_size = 8 * 512 * 512;
  auto raw_buffer = std::make_unique<uint8_t[]>(buffer_size);
  auto buffer = Buffer(raw_buffer.get());

  auto src_buffer = std::make_unique<uint8_t[]>(buffer_size);
  auto dst_buffer = std::make_unique<uint8_t[]>(buffer_size);

  for (auto _ : state) {
    auto write_ptr = buffer.write_ptr();
    memcpy(write_ptr, src_buffer.get(), buffer_size);
    buffer.commit_write();

    benchmark::DoNotOptimize(src_buffer.get());
    benchmark::DoNotOptimize(dst_buffer.get());
    benchmark::DoNotOptimize(raw_buffer.get());

    auto read_buffer = buffer.read_ptr();
    memcpy(dst_buffer.get(), read_buffer, buffer_size);
    buffer.commit_read();
  }

  state.counters["Transfers"] = benchmark::Counter(
      static_cast<double>(state.iterations() * 2), benchmark::Counter::kIsRate);

  state.counters["Bandwidth"] = benchmark::Counter(
      static_cast<double>(state.iterations() * 2) * 8 * 512 * 512,
      benchmark::Counter::kIsRate, benchmark::Counter::kIs1024);
}

BENCHMARK(BM_NoMemoryTransfer)->MinTime(5.0);
BENCHMARK(BM_WithMemoryTransfer)->MinTime(5.0);

BENCHMARK_MAIN();