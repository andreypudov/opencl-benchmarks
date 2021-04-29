#include "opencl-benchmarks.h"
#include <benchmark/benchmark.h>

extern "C" {
#include "vecmul.h"
#include "opencl.h"
}

extern cl_device_params device_params;

static void OCL_VectorMultiplication(benchmark::State& state) {
  const size_t length = 256 * 256 * 256;

  int *addend_a = (int*) malloc(sizeof(int) * length);
  int *addend_b = (int*) malloc(sizeof(int) * length);
  int *product  = (int*) malloc(sizeof(int) * length);

  cl_vecmul_params params = {
    .platform_id = device_params.platform_id,
    .device_id   = device_params.device_id,
  };

  int status = ocl_multiply_prepare(addend_a, addend_b, product, length, &params);
  if (status != CL_SUCCESS) {
    ocl_multiply_release(&params);
    return;
  }

  for (auto _ : state) {
    status = ocl_multiply_execute(&params);
    if (status != CL_SUCCESS) {
      ocl_multiply_release(&params);
      return;
    }
  }

  ocl_multiply_release(&params);

  free(addend_a);
  free(addend_b);
  free(product);
}

BENCHMARK(OCL_VectorMultiplication);