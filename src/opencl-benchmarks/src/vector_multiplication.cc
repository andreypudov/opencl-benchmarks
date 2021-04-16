#include <benchmark/benchmark.h>

static void CPU_VectorMultiplication(benchmark::State& state) {
  for (auto _ : state)
    std::string empty_string;
}

BENCHMARK(CPU_VectorMultiplication);