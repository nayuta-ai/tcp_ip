#include <gtest/gtest.h>

extern "C" {
#include "../ip.h"
#include "../platform/linux/platform.h"
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

// class TestIface : public ::testing::Test {
//  protected:
//   virtual void SetUp() {}

//   virtual void TearDown() override {}
// }

TEST(IfaceAllocTest, ValidCase) {
  struct ip_iface *iface;
  char unicast[100] = "192.168.1.1";
  char netmask[100] = "255.255.0.0";

  iface = ip_iface_alloc(unicast, netmask);

  EXPECT_EQ(iface->broadcast, 0xffffa8c0);

  memory_free(iface);
}

TEST(IpIfaceRegisterTest, ValidCase) {
  struct net_device *dev;
  struct ip_iface *iface;
  char unicast[100] = "192.168.1.1";
  char netmask[100] = "255.255.0.0";
  iface = ip_iface_alloc(unicast, netmask);
  dev = net_device_alloc();
  strcpy(dev->name, "eth0");

  int result = ip_iface_register(dev, iface);

  EXPECT_EQ(0, result);

  memory_free(iface);
  memory_free(dev);
}

TEST(IpIfaceSelectTest, ValidCase) {
  struct net_device *dev;
  struct ip_iface *iface, *entry;
  char unicast[100] = "192.168.1.1";
  char netmask[100] = "255.255.0.0";
  iface = ip_iface_alloc(unicast, netmask);
  dev = net_device_alloc();
  strcpy(dev->name, "eth0");
  ip_iface_register(dev, iface);

  entry = ip_iface_select(0x0101a8c0);

  ASSERT_TRUE(entry != NULL);

  memory_free(iface);
  memory_free(dev);
}

TEST(IpIfaceSelectTest, InvalidCase) {
  struct net_device *dev;
  struct ip_iface *iface, *entry;
  char unicast[100] = "192.168.1.1";
  char netmask[100] = "255.255.0.0";
  iface = ip_iface_alloc(unicast, netmask);
  dev = net_device_alloc();
  strcpy(dev->name, "eth0");
  ip_iface_register(dev, iface);

  entry = ip_iface_select(0x0102a8c0);

  ASSERT_TRUE(entry == NULL);

  memory_free(iface);
  memory_free(dev);
}