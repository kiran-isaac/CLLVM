#include <preprocessor.h>
#include <gtest/gtest.h>

TEST(TrigraphTest, RemoveTrigraphs) {
  std::string source = "??= ??/ ??' ??( ??) ??! ??< ??> ??- ??!";
  std::string expected = "# \\ ^ [ ] | { } ~ |";
  std::string actual = removeTrigraphs(source);
  ASSERT_EQ(expected, actual);
}