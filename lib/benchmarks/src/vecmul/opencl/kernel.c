#include "vecmul.h"

#include <opencl.h>
#include <stdio.h>
#include <stdlib.h>

int ocl_multiply_execute(cl_vecmul_params *params) {
  cl_int status = -1;

  status =  clSetKernelArg(params->kernel, 0, sizeof(cl_mem), (void*) &params->buffer_addend_a);
  status |= clSetKernelArg(params->kernel, 1, sizeof(cl_mem), (void*) &params->buffer_addend_b);
  status |= clSetKernelArg(params->kernel, 2, sizeof(cl_mem), (void*) &params->buffer_product);
  status |= clSetKernelArg(params->kernel, 3, sizeof(cl_int), (void*) &params->length);
  if (status != CL_SUCCESS) {
    fprintf(stderr, "Error: [%s] Failed to set the argument value for an argument of a kernel.\n", get_opencl_error(status));
    return (EXIT_FAILURE);
  }

  status =  clEnqueueWriteBuffer(params->command_queue, params->buffer_addend_a, CL_FALSE, 0,
    sizeof(cl_int) * params->length, params->addend_a, 0, NULL, NULL);
  status |= clEnqueueWriteBuffer(params->command_queue, params->buffer_addend_b, CL_FALSE, 0,
    sizeof(cl_int) * params->length, params->addend_b, 0, NULL, NULL);
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

  status = clEnqueueReadBuffer(params->command_queue, params->buffer_product, CL_TRUE, 0,
    sizeof(cl_int) * params->length, params->product, 0, NULL, NULL);
  if (status != CL_SUCCESS) {
    fprintf(stderr, "Error: [%s] Failed to enqueue a commands to read from a buffer object to host memory.\n", get_opencl_error(status));
    return (EXIT_FAILURE);
  }

  return (EXIT_SUCCESS);
}