#include "vector_multiplication.h"

void multiply(int *vector_a, int *vector_b, int *vector_c, size_t length) {
   for (int index = 0; index < length; ++index) {
      vector_c[index] = vector_a[index] * vector_b[index];
   }
}