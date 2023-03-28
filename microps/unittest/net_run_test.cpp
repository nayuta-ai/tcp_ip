#include <gtest/gtest.h>

extern "C" {
#include "../driver/dummy.h"
#include "../net.h"
}

// When share the global variable such devices, how to test?
TEST(NetDeviceTest, Run) {
  struct net_device *dev1;
  struct net_device *dev2;
  dev1 = dummy_init();
  dev2 = dummy_init();

  net_run();

  EXPECT_EQ(dev1->flags & NET_DEVICE_FLAG_UP, NET_DEVICE_FLAG_UP);
  EXPECT_EQ(dev2->flags & NET_DEVICE_FLAG_UP, NET_DEVICE_FLAG_UP);
}

TEST(NetDeviceTest, Close) {
  struct net_device *dev1;
  struct net_device *dev2;
  dev1 = dummy_init();
  dev2 = dummy_init();
  net_run();

  net_shutdown();

  EXPECT_EQ(dev1->flags & 0x0000, 0x0000);
  EXPECT_EQ(dev2->flags & 0x0000, 0x0000);
}