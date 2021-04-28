#ifndef OPENCL_OPENCL_H_
#define OPENCL_OPENCL_H_

#define CL_VERSION_1_2
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#ifdef __APPLE__
  #include <OpenCL/opencl.h>
#else
  #include <CL/cl.h>
#endif

typedef struct cl_params {
  cl_platform_id   platform_id;
  cl_device_id     device_id;
  cl_context       context;
  cl_command_queue command_queue;

  cl_program program;
  cl_kernel  kernel;

  cl_mem mem_addend_a;
  cl_mem mem_addend_b;
  cl_mem mem_sum;

  size_t global_work_size;
  size_t local_work_size;
} cl_params;

int prepare_opencl_device(cl_params *params);
int prepare_opencl_kernel(cl_params *params, int length);
int execute_opencl_kernel(cl_params *params, int *addend_a, int *addend_b, int *sum, int length);
int release_opencl_params(cl_params *params);

char* get_opencl_error(int errcode);

#endif // OPENCL_OPENCL_H_