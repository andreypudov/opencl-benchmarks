#include "opencl-benchmarks.h"
#include <benchmark/benchmark.h>

extern "C" {
#include "vecmul.h"
#include "opencl.h"
}

extern cl_params params;

static void CPU_VectorMultiplication(benchmark::State& state) {
  const size_t length = 8;

  int addend_a[length] = {0, 1, 2, 3, 4, 5, 6, 7};
  int addend_b[length] = {7, 6, 5, 4, 3, 2, 1, 0};
  int summary[length];

  for (auto _ : state) {
    cpu_multiply(addend_a, addend_b, summary, length);
  }
}

static void OCL_VectorMultiplication(benchmark::State& state) {
  const size_t length = 8;

  int addend_a[length] = {0, 1, 2, 3, 4, 5, 6, 7};
  int addend_b[length] = {7, 6, 5, 4, 3, 2, 1, 0};
  int summary[length];

  int status = prepare_opencl_kernel(&params, length);
  if (status != CL_SUCCESS) {
    // release_opencl_params(&params);
    // return (EXIT_FAILURE);
  }

  for (auto _ : state) {
    status = execute_opencl_kernel(&params, addend_a, addend_b, summary, length);
    if (status != CL_SUCCESS) {
      // release_opencl_params(&params);
      // return (EXIT_FAILURE);
    }
  }
}

BENCHMARK(CPU_VectorMultiplication);
BENCHMARK(OCL_VectorMultiplication);