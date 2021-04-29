#include "vecmul.h"
#include <math.h>

void cpu_multiply(int *addend_a, int *addend_b, int *product, size_t length) {
  for (int index = 0; index < length; ++index) {
    product[index] = atan(addend_a[index]) * atan(addend_b[index]);
  }
}