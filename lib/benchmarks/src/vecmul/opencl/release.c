#include "vecmul.h"
#include <stdlib.h>

int ocl_multiply_release(cl_vecmul_params *params) {
  if (params->buffer_addend_a) clReleaseMemObject(params->buffer_addend_a);
  if (params->buffer_addend_b) clReleaseMemObject(params->buffer_addend_b);
  if (params->buffer_product)  clReleaseMemObject(params->buffer_product);

  if (params->kernel)  clReleaseKernel(params->kernel);
  if (params->program) clReleaseProgram(params->program);

  if (params->command_queue) clReleaseCommandQueue(params->command_queue);
  if (params->context)       clReleaseContext(params->context);

  return (EXIT_SUCCESS);
}