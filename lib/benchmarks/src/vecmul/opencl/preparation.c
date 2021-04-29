#include "vecmul.h"
#include <opencl.h>
#include <stdio.h>
#include <stdlib.h>

const char KERNEL_NAME[]   = "multiply";
const char *KERNEL_SOURCE =
"__kernel void multiply(__global int *addend_a, __global int *addend_b, __global int *product, const int length) {" \
"  const int id = get_global_id(0);"
"  if (id < length) {" \
"    product[id] = atan((float) addend_a[id]) * atan((float) addend_b[id]);" \
"  }" \
"}";

size_t smallest_multiple(size_t value, size_t minimum);

int ocl_multiply_prepare(int *addend_a, int *addend_b, int *product, size_t length, cl_vecmul_params *params) {
  params->addend_a = addend_a;
  params->addend_b = addend_b;
  params->product = product;
  params->length = length;

  params->local_work_size = 256;
  params->global_work_size = smallest_multiple(params->local_work_size, params->length);

  cl_int status = -1;

  params->context = clCreateContext(NULL, 1, &params->device_id, NULL, NULL, &status);
  if (status != CL_SUCCESS) {
    fprintf(stderr, "Error: [%s] Failed to create an OpenCL context.\n", get_opencl_error(status));
    return (EXIT_FAILURE);
  }

  params->command_queue = clCreateCommandQueue(params->context, params->device_id, 0, &status);
  if (status != CL_SUCCESS) {
    fprintf(stderr, "Error: [%s] Failed to create a command-queue on a device.\n", get_opencl_error(status));
    return (EXIT_FAILURE);
  }

  params->buffer_addend_a = clCreateBuffer(params->context, CL_MEM_READ_ONLY,  sizeof(cl_int) * params->length, NULL, &status);
  params->buffer_addend_b = clCreateBuffer(params->context, CL_MEM_READ_ONLY,  sizeof(cl_int) * params->length, NULL, &status);
  params->buffer_product  = clCreateBuffer(params->context, CL_MEM_WRITE_ONLY, sizeof(cl_int) * params->length, NULL, &status);
  if ((params->buffer_addend_a == NULL) || (params->buffer_addend_b == NULL) || (params->buffer_product == NULL)) {
    fprintf(stderr, "Error: [%s] Failed to create a buffer object.\n", get_opencl_error(status));
    return (EXIT_FAILURE);
  }

  params->program = clCreateProgramWithSource(params->context, 1, (const char **) &KERNEL_SOURCE, NULL, &status);
  if (status != CL_SUCCESS) {
    fprintf(stderr, "Error: [%s] Failed to create a program object for a context, " \
      "or loads specified source code into the program object.\n",
      get_opencl_error(status));
    return (EXIT_FAILURE);
  }

  status = clBuildProgram(params->program, 0, NULL, NULL, NULL, NULL);
  if (status != CL_SUCCESS) {
    fprintf(stderr, "Error: [%s] Failed to build a program executable from the program source or binary.\n", get_opencl_error(status));
    return (EXIT_FAILURE);
  }

  params->kernel = clCreateKernel(params->program, KERNEL_NAME, &status);
  if (status != CL_SUCCESS) {
    fprintf(stderr, "Error: [%s] Failed to create a kernal object.\n", get_opencl_error(status));
    return (EXIT_FAILURE);
  }

  return (EXIT_SUCCESS);
}

size_t smallest_multiple(size_t value, size_t minimum) {
  size_t index = 1;

  while ((index * value) < minimum) {
    index++;
  }

  return index * value;
}