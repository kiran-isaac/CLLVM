#include <args.h>
#include <preprocessor/preprocessor.h>
#include <gtest/gtest.h>

TEST(Preprocessor, RemoveTrigraphs) {
  std::string source = "??= ??/ ??' ??( ??) ??! ??< ??> ??- ??!";
  std::string expected = "# \\ ^ [ ] | { } ~ |";
  removeTrigraphs(source);
  ASSERT_EQ(expected, source);
}

TEST(Preprocessor, RemoveLineSplices) {
  std::string source = "line1 \\  \n"
                       "line2 \\\t\t\r   \n"
                       "line3";
  std::string expected = "line1 line2 line3";
  removeLineSplices(source);
  ASSERT_EQ(expected, source);
}

TEST(Preprocessor, SingleLineComment) {
  std::string source = "line1 // comment\n"
                       "line2";
  std::string expected = "line1 \n"
                         "line2";
  removeComments(source);
  ASSERT_EQ(expected, source);
}

TEST(Preprocessor, MultiLineComment) {
  std::string source = "line1 /* comment\n"
                       "comment */ line2";
  std::string expected = "line1  line2";
  removeComments(source);
  ASSERT_EQ(expected, source);
}