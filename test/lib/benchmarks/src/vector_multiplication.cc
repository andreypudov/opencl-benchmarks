#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C" {
#include "vector_multiplication.h"
}

TEST(vector_multiplication, multiply) {
  const size_t length = 8;

  int vector_a[length] = {0, 1, 2, 3, 4, 5, 6, 7};
  int vector_b[length] = {7, 6, 5, 4, 3, 2, 1, 0};
  int vector_c[length];
  int expected_c[length] = {0, 6, 10, 12, 12, 10, 6, 0};

  multiply(vector_a, vector_b, vector_c, length);

  EXPECT_THAT(expected_c, testing::ContainerEq(vector_c));
}