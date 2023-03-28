#include <gtest/gtest.h>

extern "C" {
#include "../driver/dummy.h"
#include "../net.h"
}

TEST(NetDeviceAllocTest, ValidCase) {
  struct net_device *dev;
  dev = net_device_alloc();
  EXPECT_TRUE(dev);
}

TEST(NetDeviceRegisterTest, ValidCase) {
  struct net_device *dev1;
  struct net_device *dev2;
  dev1 = net_device_alloc();
  dev2 = net_device_alloc();

  int result1 = net_device_register(dev1);
  int result2 = net_device_register(dev2);

  EXPECT_EQ(result1, 0);
  EXPECT_EQ(result2, 0);
  EXPECT_EQ(dev1->next, nullptr);
  EXPECT_EQ(dev1->index, 0);
  EXPECT_EQ(dev2->next, dev1);
  EXPECT_EQ(dev2->index, 1);
}
