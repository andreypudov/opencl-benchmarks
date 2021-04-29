#include "opencl.h"
#include <stdlib.h>

int release_opencl_params(cl_device_params *params) {
  if (params->device_id) clReleaseDevice(params->device_id);

  return (EXIT_SUCCESS);
}