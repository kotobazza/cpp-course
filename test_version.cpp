#include <gtest/gtest.h>
#include "lib.h"

// Demonstrate some basic assertions.
TEST(TestVerions, BasicAssertions) {
  EXPECT_GT(version(), 0);
}