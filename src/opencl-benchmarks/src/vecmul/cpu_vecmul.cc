#include "opencl-benchmarks.h"
#include <benchmark/benchmark.h>

extern "C" {
#include "vecmul.h"
}

static void CPU_VectorMultiplication(benchmark::State& state) {
  const size_t length = 256 * 256 * 256;

  int *addend_a = (int*) malloc(sizeof(int) * length);
  int *addend_b = (int*) malloc(sizeof(int) * length);
  int *product  = (int*) malloc(sizeof(int) * length);

  for (auto _ : state) {
    cpu_multiply(addend_a, addend_b, product, length);
  }

  free(addend_a);
  free(addend_b);
  free(product);
}

BENCHMARK(CPU_VectorMultiplication)->Unit(benchmark::kMillisecond);