#include "opencl.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>

void fill_array(float *array, const int length);
int validate_output(const float *addend_a, const float *addend_b, float *sum, const int length);

size_t smallest_multiple(size_t value, size_t minimum);

enum { NUMBER_OF_ELEMENTS = 1024 };

int _main_(/* int argc, const char *argv[] */) {
  cl_params params = {
    .global_work_size = NUMBER_OF_ELEMENTS,
    .local_work_size  = 256
  };

  cl_int status = prepare_opencl_device(&params);
  if (status != CL_SUCCESS) {
    release_opencl_params(&params);
    return (EXIT_FAILURE);
  }

  params.local_work_size  = 256;
  params.global_work_size = smallest_multiple(params.local_work_size, NUMBER_OF_ELEMENTS);

  release_opencl_params(&params);

  return (EXIT_SUCCESS);
}

size_t smallest_multiple(size_t value, size_t minimum) {
  size_t index = 1;

  while ((index * value) < minimum) {
    index++;
  }

  return index * value;
}