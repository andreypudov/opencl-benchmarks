#ifndef BENCHMARKS_VECTOR_MULTIPLICATION_H_
#define BENCHMARKS_VECTOR_MULTIPLICATION_H_

#include <stdlib.h>

void cpu_multiply(int *vector_a, int *vector_b, int *vector_c, size_t length);
void ocl_multiply(int *vector_a, int *vector_b, int *vector_c, size_t length);

#endif // BENCHMARKS_VECTOR_MULTIPLICATION_H_