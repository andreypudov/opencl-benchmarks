#ifndef OPENCL_OPENCL_H_
#define OPENCL_OPENCL_H_

#define CL_VERSION_1_2
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#ifdef __APPLE__
  #include <OpenCL/opencl.h>
#else
  #include <CL/cl.h>
#endif

typedef struct cl_device_params {
  cl_platform_id platform_id;
  cl_device_id   device_id;
} cl_device_params;

int prepare_opencl_device(cl_device_params *device_params);
int release_opencl_params(cl_device_params *device_params);
char* get_opencl_error(int errcode);

#endif // OPENCL_OPENCL_H_