#include <gtest/gtest.h>

extern "C" {
#include "../driver/dummy.h"
#include "../ip.h"
#include "../net.h"
#include "../platform/linux/platform.h"
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

TEST(NetDeviceAddIfaceTest, ValidCase) {
  struct net_device *dev;
  struct net_iface *iface;
  dev = net_device_alloc();
  strcpy(dev->name, "eth0");
  dev->ifaces = NULL;
  iface = (struct net_iface *)ip_iface_alloc("192.168.1.1", "255.255.0.0");

  int result = net_device_add_iface(dev, iface);

  EXPECT_EQ(result, 0);

  memory_free(iface);
  memory_free(dev);
}

TEST(NetDeviceAddIfaceTest, InvalidCase) {
  struct net_device *dev;
  struct net_iface *iface;
  dev = net_device_alloc();
  strcpy(dev->name, "eth0");
  dev->ifaces = NULL;
  iface = (struct net_iface *)ip_iface_alloc("192.168.1.1", "255.255.0.0");

  net_device_add_iface(dev, iface);
  int result = net_device_add_iface(dev, iface);

  EXPECT_EQ(result, -1);

  memory_free(iface);
  memory_free(dev);
}

TEST(NetDeviceGetIfaceTest, IfaceFound) {
  struct net_device *dev;
  struct net_iface *iface, *entry;
  dev = net_device_alloc();
  strcpy(dev->name, "eth0");
  dev->ifaces = NULL;
  iface = (struct net_iface *)ip_iface_alloc("192.168.1.1", "255.255.0.0");
  net_device_add_iface(dev, iface);

  entry = net_device_get_iface(dev, NET_IFACE_FAMILY_IP);

  ASSERT_TRUE(entry != NULL);

  memory_free(iface);
  memory_free(dev);
}

TEST(NetDeviceGetIfaceTest, IfaceNotFound) {
  struct net_device *dev;
  struct net_iface *iface, *entry;
  dev = net_device_alloc();
  strcpy(dev->name, "eth0");
  dev->ifaces = NULL;
  iface = (struct net_iface *)ip_iface_alloc("192.168.1.1", "255.255.0.0");
  net_device_add_iface(dev, iface);

  entry = net_device_get_iface(dev, NET_IFACE_FAMILY_IPV6);

  ASSERT_TRUE(entry == NULL);

  memory_free(iface);
  memory_free(dev);
}