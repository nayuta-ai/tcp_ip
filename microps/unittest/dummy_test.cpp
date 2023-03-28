#include <gtest/gtest.h>

extern "C" {
#include "../driver/dummy.h"
#include "../net.h"
}

TEST(DummyTest, ValidStructure) {
  struct net_device *dev;

  dev = dummy_init();

  EXPECT_TRUE(dev != NULL);
  EXPECT_EQ(NET_DEVICE_TYPE_DUMMY, dev->type);
  EXPECT_EQ(UINT16_MAX, dev->mtu);
  EXPECT_EQ(0, dev->hlen);
  EXPECT_EQ(0, dev->alen);
}