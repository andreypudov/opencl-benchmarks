#ifndef BENCHMARKS_VECMUL_H_
#define BENCHMARKS_VECMUL_H_

#include <stdlib.h>

#define CL_VERSION_1_2
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#ifdef __APPLE__
  #include <OpenCL/opencl.h>
#else
  #include <CL/cl.h>
#endif

typedef struct cl_vecmul_params {
  cl_platform_id platform_id;
  cl_device_id   device_id;

  cl_context       context;
  cl_command_queue command_queue;

  cl_program program;
  cl_kernel  kernel;

  int *addend_a;
  int *addend_b;
  int *product;
  cl_int length;

  cl_mem buffer_addend_a;
  cl_mem buffer_addend_b;
  cl_mem buffer_product;

  size_t global_work_size;
  size_t local_work_size;
} cl_vecmul_params;


void cpu_multiply(int *addend_a, int *addend_b, int *product, size_t length);

int ocl_multiply_prepare(int *addend_a, int *addend_b, int *product, size_t length, cl_vecmul_params *params);
int ocl_multiply_execute(cl_vecmul_params *params);
int ocl_multiply_release(cl_vecmul_params *params);

#endif // BENCHMARKS_VECMUL_H_