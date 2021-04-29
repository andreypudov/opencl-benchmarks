#include "opencl-benchmarks.h"
#include <benchmark/benchmark.h>

cl_device_params device_params;

int main(int argc, char *argv[]) {
  cl_int status = prepare_opencl_device(&device_params);
  if (status != CL_SUCCESS) {
    release_opencl_params(&device_params);
    return (EXIT_FAILURE);
  }

  ::benchmark::Initialize(&argc, argv);
  ::benchmark::RunSpecifiedBenchmarks();

  release_opencl_params(&device_params);

  return (EXIT_SUCCESS);
}