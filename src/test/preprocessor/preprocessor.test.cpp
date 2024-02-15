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

TEST(Preprocessor, RemoveSingleLineComments) {
  std::string source = "a // b\n c";
  std::string expected = "a \n c";
  std::string actual = removeComments(source);
  ASSERT_EQ(expected, actual);
}

TEST(Preprocessor, RemoveMultiLineComments) {
  std::string source = "a /* b */ c";
  std::string expected = "a  c";
  std::string actual = removeComments(source);
  ASSERT_EQ(expected, actual);
}