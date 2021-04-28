#include "opencl-benchmarks.h"
#include <benchmark/benchmark.h>

cl_params params;

int main(int argc, char *argv[]) {
  enum { NUMBER_OF_ELEMENTS = 1024 };

  params = {
    .global_work_size = NUMBER_OF_ELEMENTS,
    .local_work_size  = 256
  };

  cl_int status = prepare_opencl_device(&params);
  if (status != CL_SUCCESS) {
    release_opencl_params(&params);
    return (EXIT_FAILURE);
  }

  ::benchmark::Initialize(&argc, argv);
  ::benchmark::RunSpecifiedBenchmarks();

  release_opencl_params(&params);

  return (EXIT_SUCCESS);
}