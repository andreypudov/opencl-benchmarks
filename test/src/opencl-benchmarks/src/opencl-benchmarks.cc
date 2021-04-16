#include "gtest/gtest.h"

TEST(vector_multiplication, multiply) {
  EXPECT_EQ(1, 1);
}

auto main(int argc, char *argv[]) -> decltype(RUN_ALL_TESTS()) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}