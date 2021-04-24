#include <benchmark/benchmark.h>

extern "C" {
#include "vector_multiplication.h"
}

static void CPU_VectorMultiplication(benchmark::State& state) {
  const size_t length = 8;

  int vector_a[length] = {0, 1, 2, 3, 4, 5, 6, 7};
  int vector_b[length] = {7, 6, 5, 4, 3, 2, 1, 0};
  int vector_c[length];

  for (auto _ : state) {
    multiply(vector_a, vector_b, vector_c, length);
  }
}

BENCHMARK(CPU_VectorMultiplication);