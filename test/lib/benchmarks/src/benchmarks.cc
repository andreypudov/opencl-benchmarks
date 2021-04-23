#include "gtest/gtest.h"

auto main(int argc, char *argv[]) -> decltype(RUN_ALL_TESTS()) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}