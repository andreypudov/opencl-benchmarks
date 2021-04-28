#include "opencl.h"

#include <stdio.h>
#include <stdlib.h>

const char KERNEL_NAME[]   = "multiply";
const char *KERNEL_SOURCE =
"__kernel void multiply(__global int *vector_a, __global int *vector_b, __global int *vector_c, const int length) {" \
"  const int id = get_global_id(0);"
"  if (id < length) {" \
"    vector_c[id] = vector_a[id] * vector_b[id];" \
"  }" \
"}";

int prepare_opencl_kernel(cl_params *params, int length) {
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

  params->mem_addend_a = clCreateBuffer(params->context, CL_MEM_READ_ONLY,  sizeof(cl_int) * length, NULL, &status);
  params->mem_addend_b = clCreateBuffer(params->context, CL_MEM_READ_ONLY,  sizeof(cl_int) * length, NULL, &status);
  params->mem_sum      = clCreateBuffer(params->context, CL_MEM_WRITE_ONLY, sizeof(cl_int) * length, NULL, &status);
  if ((params->mem_addend_a == NULL) || (params->mem_addend_b == NULL) || (params->mem_sum == NULL)) {
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
    // free(kernel_binary);
    return (EXIT_FAILURE);
  }

  params->kernel = clCreateKernel(params->program, KERNEL_NAME, &status);
  if (status != CL_SUCCESS) {
    fprintf(stderr, "Error: [%s] Failed to create a kernal object.\n", get_opencl_error(status));
    // free(kernel_binary);
    return (EXIT_FAILURE);
  }

  return (EXIT_SUCCESS);
}

int execute_opencl_kernel(cl_params *params, int *addend_a, int *addend_b, int *sum, int length) {
  cl_int number_of_elements = length;
  cl_int status = -1;

  status =  clSetKernelArg(params->kernel, 0, sizeof(cl_mem), (void*) &params->mem_addend_a);
  status |= clSetKernelArg(params->kernel, 1, sizeof(cl_mem), (void*) &params->mem_addend_b);
  status |= clSetKernelArg(params->kernel, 2, sizeof(cl_mem), (void*) &params->mem_sum);
  status |= clSetKernelArg(params->kernel, 3, sizeof(cl_int), (void*) &number_of_elements);
  if (status != CL_SUCCESS) {
    fprintf(stderr, "Error: [%s] Failed to set the argument value for an argument of a kernel.\n", get_opencl_error(status));
    return (EXIT_FAILURE);
  }

  status =  clEnqueueWriteBuffer(params->command_queue, params->mem_addend_a, CL_FALSE, 0,
    sizeof(cl_int) * length, addend_a, 0, NULL, NULL);
  status |= clEnqueueWriteBuffer(params->command_queue, params->mem_addend_b, CL_FALSE, 0,
    sizeof(cl_int) * length, addend_b, 0, NULL, NULL);
  if (status != CL_SUCCESS) {
    fprintf(stderr, "Error: [%s] Failed to enqueue a command to write to a buffer object from host memory.\n", get_opencl_error(status));
    return (EXIT_FAILURE);
  }

  status = clGetKernelWorkGroupInfo(params->kernel, params->device_id, CL_KERNEL_WORK_GROUP_SIZE,
    sizeof(params->local_work_size), &params->local_work_size, NULL);
  if (status != CL_SUCCESS) {
    fprintf(stderr, "Error: [%s] Failed to obtain information about the kernel object.\n", get_opencl_error(status));
    return (EXIT_FAILURE);
  }

  status = clEnqueueNDRangeKernel(params->command_queue, params->kernel, 1, NULL,
    &params->global_work_size, &params->local_work_size, 0, NULL, NULL);
  if (status != CL_SUCCESS) {
    fprintf(stderr, "Error: [%s] Failed to enqueue a command to execute a kernel on a device.\n", get_opencl_error(status));
    return (EXIT_FAILURE);
  }

  status = clEnqueueReadBuffer(params->command_queue, params->mem_sum, CL_TRUE, 0,
    sizeof(cl_int) * length, sum, 0, NULL, NULL);
  if (status != CL_SUCCESS) {
    fprintf(stderr, "Error: [%s] Failed to enqueue a commands to read from a buffer object to host memory.\n", get_opencl_error(status));
    return (EXIT_FAILURE);
  }

  return (EXIT_SUCCESS);
}