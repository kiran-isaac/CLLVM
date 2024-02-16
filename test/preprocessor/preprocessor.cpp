#include <args.h>
#include <lexer.h>
#include <gtest/gtest.h>

TEST(LexerPreprocess, RemoveTrigraphs) {
  std::string source = "??= ??/ ??' ??( ??) ??! ??< ??> ??- ??!";
  std::string expected = "# \\ ^ [ ] | { } ~ |";
  Lexer lexer = Lexer(source);

  ASSERT_EQ(expected, *lexer.getSource());
}

// Line splices must be the last character on a line
TEST(LexerPreprocess, RemoveLineSplices) {
  std::string source = "line1 \\\n"
                       "line2 \\\n"
                       "line3";
  std::string expected = "line1 line2 line3";
  Lexer lexer = Lexer(source);
  lexer.preprocess();
  ASSERT_EQ(expected, lexer.sourceFromTokens());
}

TEST(Preprocessor, SingleLineComment) {
  std::string source = "line1 // comment\n"
                       "line2";
  std::string expected = "line1 \n line2";

  Lexer lexer = Lexer(source);
  lexer.preprocess();
  ASSERT_EQ(expected, lexer.sourceFromTokens());
}

TEST(Preprocessor, MultiLineComment) {
  std::string source = "line1 /* comment\n"
                       "comment */ line2";
  std::string expected = "line1 line2";

  Lexer lexer = Lexer(source);
  lexer.preprocess();
  ASSERT_EQ(expected, lexer.sourceFromTokens());
}