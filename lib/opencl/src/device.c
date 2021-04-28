#include "opencl.h"

#include <stdio.h>
#include <stdlib.h>

cl_platform_id select_opencl_platform(void);
cl_device_id select_opencl_device(cl_platform_id platform_id);

enum { BUFFER_LENGTH = 1024 };

int prepare_opencl_device(cl_params *params) {
  char platform_buffer[BUFFER_LENGTH];
  char device_buffer[BUFFER_LENGTH];
  cl_int status = -1;

  params->platform_id = select_opencl_platform();
  if (params->platform_id == NULL) {
    return (EXIT_FAILURE);
  }

  status = clGetPlatformInfo(params->platform_id, CL_PLATFORM_NAME, BUFFER_LENGTH, &platform_buffer, NULL);
  if (status != CL_SUCCESS) {
    fprintf(stderr, "Error: [%s] Failed to get information about the OpenCL platform.\n", get_opencl_error(status));
    return (EXIT_FAILURE);
  }

  params->device_id = select_opencl_device(params->platform_id);
  if (params->device_id == NULL) {
    return (EXIT_FAILURE);
  }

  status = clGetDeviceInfo(params->device_id, CL_DEVICE_NAME, BUFFER_LENGTH, &device_buffer, NULL);
  if (status != CL_SUCCESS) {
    fprintf(stderr, "Error: [%s] Failed to get information about an OpenCL device.\n", get_opencl_error(status));
    return (EXIT_FAILURE);
  }

  fprintf(stdout, "OpenCL platform: %s\n", platform_buffer);
  fprintf(stdout, "OpenCL device: %s\n", device_buffer);

  return (EXIT_SUCCESS);
}

cl_platform_id select_opencl_platform() {
  cl_platform_id *list_of_platform_ids = NULL;
  cl_platform_id selected_platform_id  = NULL;
  cl_uint        number_of_platforms   = -1U;

  const char buffer[BUFFER_LENGTH];
  selected_platform_id = NULL;
  cl_int status = -1;

  status = clGetPlatformIDs(0, NULL, &number_of_platforms);
  if (status != CL_SUCCESS) {
    fprintf(stderr, "Error: [%s] Failed to obtain the number of platforms available.\n", get_opencl_error(status));
    return NULL;
  }

  list_of_platform_ids = (cl_platform_id*) malloc(sizeof(cl_platform_id) * number_of_platforms);
  if (list_of_platform_ids == NULL) {
    fprintf(stderr, "Error: Failed to allocate memory for the list of platforms.\n");
    return NULL;
  }

  status = clGetPlatformIDs(number_of_platforms, list_of_platform_ids, NULL);
  if (status != CL_SUCCESS) {
    fprintf(stderr, "Error: [%s] Failed to obtain the list of platforms available.\n", get_opencl_error(status));
    free(list_of_platform_ids);
    return NULL;
  }

  if (number_of_platforms < 1) {
    fprintf(stderr, "Error: No OpenCL platform found.\n");
    free(list_of_platform_ids);
    return NULL;
  }

  if (number_of_platforms == 1) {
    cl_platform_id platform_id = list_of_platform_ids[0];
    free(list_of_platform_ids);

    return platform_id;
  }

  fprintf(stdout, "OpenCL platforms available on the system:\n");

  for (cl_uint index = 0; index < number_of_platforms; ++index) {
    status = clGetPlatformInfo(list_of_platform_ids[index], CL_PLATFORM_NAME, BUFFER_LENGTH, (void*) buffer, NULL);
    if (status != CL_SUCCESS) {
      fprintf(stderr, "Error: [%s] Failed to get information about an OpenCL platform.\n", get_opencl_error(status));
      free(list_of_platform_ids);
      return NULL;
    }

    fprintf(stdout, "%i %s\n", index + 1, buffer);
  }

  while (selected_platform_id == NULL) {
    unsigned int selection = 0;

    fprintf(stdout, "Select an OpenCL platform [1 - %i]: ", number_of_platforms);
    scanf("%i", &selection);

    if ((selection < 1) || (selection > (number_of_platforms))) {
      fprintf(stdout, "Invalid input, please try again.\n");
      continue;
    }

    selected_platform_id = list_of_platform_ids[selection - 1];
  }

  free(list_of_platform_ids);

  return selected_platform_id;
}

cl_device_id select_opencl_device(cl_platform_id platform_id) {
  cl_device_id *list_of_device_ids = NULL;
  cl_device_id selected_device_id  = NULL;
  cl_uint      number_of_devices   = -1U;

  const char buffer[BUFFER_LENGTH];
  selected_device_id = NULL;
  cl_int status = -1;

  status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 0, NULL, &number_of_devices);
  if (status != CL_SUCCESS) {
    fprintf(stderr, "Error: [%s] Failed to obtain the number of devices available.\n", get_opencl_error(status));
    return NULL;
  }

  list_of_device_ids = (cl_device_id*) malloc(sizeof(cl_device_id) * number_of_devices);
  if (list_of_device_ids == NULL) {
    fprintf(stderr, "Error: Failed to allocate memory for the list of devices.\n");
    return NULL;
  }

  status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, number_of_devices, list_of_device_ids, NULL);
  if (status != CL_SUCCESS) {
    fprintf(stderr, "Error: [%s] Failed to obtain the list of devices available on a platform.\n", get_opencl_error(status));
    free(list_of_device_ids);
    return NULL;
  }

  if (number_of_devices < 1) {
    fprintf(stderr, "Error: No OpenCL platform found.\n");
    free(list_of_device_ids);
    return NULL;
  }

  if (number_of_devices == 1) {
    selected_device_id = list_of_device_ids[0];
    free(list_of_device_ids);

    return selected_device_id;
  }

  fprintf(stdout, "OpenCL devices available on the system:\n");

  for (cl_uint index = 0; index < number_of_devices; ++index) {
    status = clGetDeviceInfo(list_of_device_ids[index], CL_DEVICE_NAME, BUFFER_LENGTH, (void*) buffer, NULL);
    if (status != CL_SUCCESS) {
      fprintf(stderr, "Error: [%s] Failed to get information about an OpenCL device.\n", get_opencl_error(status));
      free(list_of_device_ids);
      return NULL;
    }

    fprintf(stdout, "%i %s\n", index + 1, buffer);
  }

  while (selected_device_id == NULL) {
    unsigned int selection = 0;

    fprintf(stdout, "Select an OpenCL device [1 - %i]: ", number_of_devices);
    scanf("%i", &selection);

    if ((selection < 1) || (selection > (number_of_devices))) {
      fprintf(stdout, "Invalid input, please try again.\n");
      continue;
    }

    selected_device_id = list_of_device_ids[selection - 1];
  }

  free(list_of_device_ids);

  return selected_device_id;
}