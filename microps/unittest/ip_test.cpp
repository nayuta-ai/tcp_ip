#include <gtest/gtest.h>

extern "C" {
#include "../ip.h"
}

TEST(IpInitTest, ValidCase) {
  int result = ip_init();

  EXPECT_EQ(0, result);
}

TEST(IpInitTest, FailuCase) {
  ip_init();

  int result = ip_init();

  EXPECT_EQ(-1, result);
}