#include "opencl.h"

#include <stdlib.h>

int release_opencl_params(cl_params *params) {
  if (params->mem_addend_a) clReleaseMemObject(params->mem_addend_a);
  if (params->mem_addend_b) clReleaseMemObject(params->mem_addend_b);
  if (params->mem_sum)      clReleaseMemObject(params->mem_sum);

  if (params->kernel)  clReleaseKernel(params->kernel);
  if (params->program) clReleaseProgram(params->program);

  if (params->command_queue) clReleaseCommandQueue(params->command_queue);
  if (params->context)       clReleaseContext(params->context);

  if (params->device_id) clReleaseDevice(params->device_id);

  return (EXIT_SUCCESS);
}