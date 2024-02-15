#include <preprocessor/preprocessor.h>
#include <gtest/gtest.h>

TEST(Preprocessor, RemoveTrigraphs) {
  std::string source = "??= ??/ ??' ??( ??) ??! ??< ??> ??- ??!";
  std::string expected = "# \\ ^ [ ] | { } ~ |";
  std::string actual = removeTrigraphs(source);
  ASSERT_EQ(expected, actual);
}

TEST(Preprocessor, RemoveLineSplices) {
  std::string source = "a\\\nb";
  std::string expected = "ab";
  std::string actual = removeLineSplices(source);
  ASSERT_EQ(expected, actual);
}
