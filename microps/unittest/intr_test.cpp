#include <gtest/gtest.h>

extern "C" {
#include "../platform/linux/platform.h"
}

TEST(IntrRequestIrqTest, RegisterTest) {
  unsigned int irq = 10;
  int flags = INTR_IRQ_SHARED;
  const char *name = "valid_irq_test";
  void *dev = nullptr;

  int result = intr_request_irq(irq, nullptr, flags, name, dev);

  EXPECT_EQ(0, result);
}

TEST(IntrRequestIrqTest, InvalidRegisterTest) {
  unsigned int irq1 = 11;
  int flags1 = INTR_IRQ_SHARED;
  const char *name1 = "valid_irq_test";
  void *dev1 = nullptr;

  int result1 = intr_request_irq(irq1, nullptr, flags1, name1, dev1);

  EXPECT_EQ(0, result1);

  unsigned int irq2 = 11;
  int flags2 = 0x0000;
  const char *name2 = "invalid_irq_test";
  void *dev2 = nullptr;

  int result2 = intr_request_irq(irq2, nullptr, flags2, name2, dev2);

  EXPECT_EQ(-1, result2);
}