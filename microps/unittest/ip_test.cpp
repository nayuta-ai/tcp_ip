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

TEST(IpAddrPtonTest, ValidCase) {
  ip_addr_t addr;

  ASSERT_EQ(ip_addr_pton("192.168.1.1", &addr), 0);
  EXPECT_EQ(192, ((uint8_t *)&addr)[0]);
  EXPECT_EQ(168, ((uint8_t *)&addr)[1]);
  EXPECT_EQ(1, ((uint8_t *)&addr)[2]);
  EXPECT_EQ(1, ((uint8_t *)&addr)[3]);
}

TEST(IpAddrPtonTest, InvalidCase) {
  ip_addr_t addr;
  ASSERT_EQ(ip_addr_pton("256.168.1.1", &addr), -1);  // Out of range
  ASSERT_EQ(ip_addr_pton("256.168.1", &addr), -1);
  ASSERT_EQ(ip_addr_pton("256.168.1.1.1", &addr), -1);
}

TEST(IpAddrNtopTest, ValidCase) {
  char p[200];
  EXPECT_STREQ("255.255.255.255", ip_addr_ntop(0xffffffff, p, 32 * 4));
}