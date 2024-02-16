#include <args.h>
#include <gtest/gtest.h>
#include <lexer.h>
#include <tokens.h>

#define ASSERT_TOKEN(x)                                                        \
  ASSERT_EQ(token.type, CToken::x);                                            \
  token = lexer.next_token();

TEST(Lexer, StringsAreMatchedCorrectly) {
  std::string source = "  printf(\"Hello, World!\n\");\n"
                       "  printf(\"Hello, World!\n\")";

  Lexer lexer = Lexer(source);
  Token token = lexer.next_token();
  ASSERT_TOKEN(CIdentifier);
  ASSERT_TOKEN(CPunctuation_LeftParenthesis);
  ASSERT_TOKEN(CConstant_String);
  ASSERT_TOKEN(CPunctuation_RightParenthesis);
  ASSERT_TOKEN(CPunctuation_Semicolon);
}

TEST(Lexer, HelloWorld) {
  std::string source = "#include <stdio.h>\n"
                       "\n"
                       "int main() {\n"
                       "  printf(\"Hello, World!\\n\");\n"
                       "  return 0;\n"
                       "}";
  Lexer lexer = Lexer(source);

  Token token = lexer.next_token();
  ASSERT_TOKEN(CPreprocessorDirective_Include);
  ASSERT_TOKEN(COperator_LessThan);
  ASSERT_TOKEN(CIdentifier);
  ASSERT_TOKEN(COperator_Dot);
  ASSERT_TOKEN(CIdentifier);
  ASSERT_TOKEN(COperator_GreaterThan);
  ASSERT_TOKEN(CNewline);
  ASSERT_TOKEN(CNewline);
  ASSERT_TOKEN(CKeyword_Int);
  ASSERT_TOKEN(CIdentifier);
  ASSERT_TOKEN(CPunctuation_LeftParenthesis);
  ASSERT_TOKEN(CPunctuation_RightParenthesis);
  ASSERT_TOKEN(CPunctuation_LeftBrace);
  ASSERT_TOKEN(CNewline);
  ASSERT_TOKEN(CIdentifier);
  ASSERT_TOKEN(CPunctuation_LeftParenthesis);
  ASSERT_TOKEN(CConstant_String);
  ASSERT_TOKEN(CPunctuation_RightParenthesis);
  ASSERT_TOKEN(CPunctuation_Semicolon);
  ASSERT_TOKEN(CNewline);
  ASSERT_TOKEN(CKeyword_Return);
  ASSERT_TOKEN(CConstant_Integer);
  ASSERT_TOKEN(CPunctuation_Semicolon);
  ASSERT_TOKEN(CNewline);
  ASSERT_TOKEN(CPunctuation_RightBrace);
  ASSERT_TOKEN(CEOF);
}

TEST(Lexer, HelloWorldWithMorePreprocessorDirectives) {
  // Preprocessor directives can be anywhere in the source code and there can be
  // any whitespace before or after the hashtag
  std::string source = "\t\t#\r\r\n\tinclude <stdio.h>\n"
                       "\n"
                       "\r\t#\t\t\ndefine HELLO \"Hello, World!\\n\"\n"
                       "int main() {\n"
                       "  printf(HELLO);\n"
                       "  return 0;\n"
                       "}";
  Lexer lexer = Lexer(source);

  Token token = lexer.next_token();
  ASSERT_TOKEN(CPreprocessorDirective_Include);
  ASSERT_TOKEN(COperator_LessThan);
  ASSERT_TOKEN(CIdentifier);
  ASSERT_TOKEN(COperator_Dot);
  ASSERT_TOKEN(CIdentifier);
  ASSERT_TOKEN(COperator_GreaterThan);
  ASSERT_TOKEN(CNewline);
  ASSERT_TOKEN(CNewline);
  ASSERT_TOKEN(CPreprocessorDirective_Define);
  ASSERT_TOKEN(CIdentifier);
  ASSERT_TOKEN(CConstant_String);
  ASSERT_TOKEN(CNewline);
  ASSERT_TOKEN(CKeyword_Int);
  ASSERT_TOKEN(CIdentifier);
  ASSERT_TOKEN(CPunctuation_LeftParenthesis);
  ASSERT_TOKEN(CPunctuation_RightParenthesis);
  ASSERT_TOKEN(CPunctuation_LeftBrace);
  ASSERT_TOKEN(CNewline);
  ASSERT_TOKEN(CIdentifier);
  ASSERT_TOKEN(CPunctuation_LeftParenthesis);
  ASSERT_TOKEN(CIdentifier);
  ASSERT_TOKEN(CPunctuation_RightParenthesis);
  ASSERT_TOKEN(CPunctuation_Semicolon);
  ASSERT_TOKEN(CNewline);
  ASSERT_TOKEN(CKeyword_Return);
  ASSERT_TOKEN(CConstant_Integer);
  ASSERT_TOKEN(CPunctuation_Semicolon);
  ASSERT_TOKEN(CNewline);
  ASSERT_TOKEN(CPunctuation_RightBrace);
  ASSERT_TOKEN(CEOF);
}

TEST(Lexer, HelloWorldWithCommentsAndLineSplices) {
  // Preprocessor directives can be anywhere in the source code and there can be
  // any whitespace before or after the hashtag
  std::string source =
    "\t\t#\r\r\n\tinclude <stdio.h>\n"
    "\\\n" // Line splice so the newline is ignored
    "\r\t#\t\t\ndefine HELLO \"Hello, World!\\n\"\n"
    "int main() { // This comment shouldn't affect anything!!\n"
    " /* This should also do nothing \n */ printf(HELLO);\n"
    "  return 0;\n"
    "}";
  Lexer lexer = Lexer(source);
  lexer.preprocess();

  Token token = lexer.next_token();
  ASSERT_TOKEN(CPreprocessorDirective_Include);
  ASSERT_TOKEN(COperator_LessThan);
  ASSERT_TOKEN(CIdentifier);
  ASSERT_TOKEN(COperator_Dot);
  ASSERT_TOKEN(CIdentifier);
  ASSERT_TOKEN(COperator_GreaterThan);
  ASSERT_TOKEN(CNewline); // Only one newline because of the line splice
  ASSERT_TOKEN(CPreprocessorDirective_Define);
  ASSERT_TOKEN(CIdentifier);
  ASSERT_TOKEN(CConstant_String);
  ASSERT_TOKEN(CNewline);
  ASSERT_TOKEN(CKeyword_Int);
  ASSERT_TOKEN(CIdentifier);
  ASSERT_TOKEN(CPunctuation_LeftParenthesis);
  ASSERT_TOKEN(CPunctuation_RightParenthesis);
  ASSERT_TOKEN(CPunctuation_LeftBrace);
  ASSERT_TOKEN(CNewline);
  ASSERT_TOKEN(CIdentifier);
  ASSERT_TOKEN(CPunctuation_LeftParenthesis);
  ASSERT_TOKEN(CIdentifier);
  ASSERT_TOKEN(CPunctuation_RightParenthesis);
  ASSERT_TOKEN(CPunctuation_Semicolon);
  ASSERT_TOKEN(CNewline);
  ASSERT_TOKEN(CKeyword_Return);
  ASSERT_TOKEN(CConstant_Integer);
  ASSERT_TOKEN(CPunctuation_Semicolon);
  ASSERT_TOKEN(CNewline);
  ASSERT_TOKEN(CPunctuation_RightBrace);
  ASSERT_TOKEN(CEOF);
}

TEST(Lexer, OneLineColumnPosTest) {
  std::string source = "  printf(\"Hello, World!\n\");\n";

  Lexer lexer = Lexer(source);
  Token token = lexer.next_token();

  ASSERT_EQ(token.column, 3);
  ASSERT_TOKEN(CIdentifier);
  ASSERT_EQ(token.column, 9);
  ASSERT_TOKEN(CPunctuation_LeftParenthesis);
  ASSERT_EQ(token.column, 10);
  ASSERT_TOKEN(CConstant_String);
  ASSERT_EQ(token.column, 26);
  ASSERT_TOKEN(CPunctuation_RightParenthesis);
  ASSERT_EQ(token.column, 27);
  ASSERT_TOKEN(CPunctuation_Semicolon);
  ASSERT_EQ(token.column, 28);
  ASSERT_TOKEN(CNewline);
  ASSERT_EQ(token.column, 1);
}

TEST(Lexer, MultiLineColumnPosTest) {
  std::string source = "  printf(\"Hello, World!\n\");\n"
                       "  printf(\"Hello, World!\n\");\n";

  Lexer lexer = Lexer(source);
  Token token = lexer.next_token();

  ASSERT_EQ(token.column, 3);
  ASSERT_TOKEN(CIdentifier);
  ASSERT_EQ(token.column, 9);
  ASSERT_TOKEN(CPunctuation_LeftParenthesis);
  ASSERT_EQ(token.column, 10);
  ASSERT_TOKEN(CConstant_String);
  ASSERT_EQ(token.column, 26);
  ASSERT_TOKEN(CPunctuation_RightParenthesis);
  ASSERT_EQ(token.column, 27);
  ASSERT_TOKEN(CPunctuation_Semicolon);
  ASSERT_EQ(token.column, 28);

  ASSERT_TOKEN(CNewline);

  ASSERT_EQ(token.column, 3);
  ASSERT_TOKEN(CIdentifier);
  ASSERT_EQ(token.column, 9);
  ASSERT_TOKEN(CPunctuation_LeftParenthesis);
  ASSERT_EQ(token.column, 10);
  ASSERT_TOKEN(CConstant_String);
  ASSERT_EQ(token.column, 26);
  ASSERT_TOKEN(CPunctuation_RightParenthesis);
  ASSERT_EQ(token.column, 27);
  ASSERT_TOKEN(CPunctuation_Semicolon);
  ASSERT_EQ(token.column, 28);
}

TEST(Lexer, CanStringifyAnyToken) {
// Iterate through all values of the CToken enum and ensure that they can be converted to a string
  for (int i = 0; i < CTOKENS_NUM_TOKENS; i++) {
    CToken token = CToken(i);
    std::string tokenString = CTokenStringMap.at(token);
    std::cout << tokenString << std::endl;
  }
}


TEST(PreprocessorLexerIntegration, CorrectLexerLineCountsAfterPreprocessing) {
  std::string source = "line1\\\n"
                       "line2\\\n";
  Lexer lexer = Lexer(source);
  lexer.preprocess();

  std::vector<CToken> expected_tokens = {CToken::CIdentifier, CToken::CIdentifier, CToken::CEOF};
  std::vector<int> expected_lines = {1, 2, 2};

  for (int i = 0; i < expected_tokens.size(); i++) {
    Token token = lexer.next_token();
    if (token.type == CToken::CEOF) {
      break;
    }
    if (token.type != expected_tokens[i]) {
      std::cout << "TOKEN FAILURE: Expected: " << CTokenStringMap.at(expected_tokens[i]) << " at position " << i << " Got: " << CTokenStringMap.at(token.type) << std::endl;
      FAIL();
    }
    if (token.line != expected_lines[i]) {
      std::cout << "LINE FAILURE at : Expected: " << expected_lines[i] << " at position " << i << " Got: " << token.line << std::endl;
      FAIL();
    }
  }
}

TEST(PreprocessorLexerIntegration, CorrectLexerLineCountsAfterPreprocessing2) {
  std::string source = "line1\\\n"
                       "line2\\\n"
                       "line3";
  Lexer lexer = Lexer(source);
  lexer.preprocess();

  std::vector<CToken> expected_tokens = {CToken::CIdentifier, CToken::CIdentifier, CToken::CIdentifier, CToken::CEOF};
  std::vector<int> expected_lines = {1, 2, 3, 3};

  for (int i = 0; i < expected_tokens.size(); i++) {
    Token token = lexer.next_token();
    if (token.type == CToken::CEOF) {
      break;
    }
    if (token.type != expected_tokens[i]) {
      std::cout << "TOKEN FAILURE: Expected: " << CTokenStringMap.at(expected_tokens[i]) << " at position " << i << " Got: " << CTokenStringMap.at(token.type) << std::endl;
      FAIL();
    }
    if (token.line != expected_lines[i]) {
      std::cout << "LINE FAILURE at : Expected: " << expected_lines[i] << " at position " << i << " Got: " << token.line << std::endl;
      FAIL();
    }
  }
}

TEST(PreprocessorLexerIntegration, CorrectLexerLineCountsAfterPreprocessing3) {
  std::string source = "line1 /* \\\n"
                       "*/ line2\\\n"
                       "line3";
  Lexer lexer = Lexer(source);
  lexer.preprocess();

  std::vector<CToken> expected_tokens = {CToken::CIdentifier, CToken::CIdentifier, CToken::CIdentifier, CToken::CEOF};
  std::vector<int> expected_lines = {1, 1, 2, 2};

  for (int i = 0; i < expected_tokens.size(); i++) {
    Token token = lexer.next_token();
    if (token.type == CToken::CEOF) {
      break;
    }
    if (token.type != expected_tokens[i]) {
      std::cout << "TOKEN FAILURE: Expected: " << CTokenStringMap.at(expected_tokens[i]) << " at position " << i << " Got: " << CTokenStringMap.at(token.type) << std::endl;
      FAIL();
    }
    if (token.line != expected_lines[i]) {
      std::cout << "LINE FAILURE at : Expected: " << expected_lines[i] << " at position " << i << " Got: " << token.line << std::endl;
      FAIL();
    }
  }
}