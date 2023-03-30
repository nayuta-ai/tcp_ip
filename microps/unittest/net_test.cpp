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

TEST(NetProtocolRegisterTest, ValidCase) {
  uint16_t type = 0x0801;
  void (*handler)(const uint8_t *, size_t, struct net_device *) = nullptr;

  int result = net_protocol_register(type, handler);

  EXPECT_EQ(0, result);
}

TEST(NetProtocolRegisterTest, AlreadyExistCase) {
  uint16_t type = 0x0802;
  void (*handler)(const uint8_t *, size_t, struct net_device *) = nullptr;

  int result = net_protocol_register(type, handler);
  result = net_protocol_register(type, handler);

  EXPECT_EQ(-1, result);
}