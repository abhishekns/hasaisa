#include <gtest/gtest.h>
#include "flexibleObjects.hpp"

using namespace flexiobjects::properties;

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  enableLogging();
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
  NamedProperties<float, 5> props;
  std::string prop1("prop1");
  std::string prop2("prop2");
  props.addProperty(prop1);
  props.addProperty(prop2);
  auto propA = props.getProperty(prop1);
  propA->setValue(10);
  EXPECT_EQ(10, propA->getValue());
}
