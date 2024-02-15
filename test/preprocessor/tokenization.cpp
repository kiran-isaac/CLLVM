#include <args.h>
#include <gtest/gtest.h>
#include <lexer.h>
#include <preprocessor/preprocessor.h>
#include <tokens.h>

TEST(Lexer, Keyword) {
  //  CKeyword_Auto,
  //  CKeyword_Struct,
  //  CKeyword_Break,
  //  CKeyword_Else,
  //  CKeyword_Long,
  //  CKeyword_Switch,
  //  CKeyword_Case,
  //  CKeyword_Enum,
  //  CKeyword_Register,
  //  CKeyword_Typedef,
  //  CKeyword_Extern,
  //  CKeyword_Return,
  //  CKeyword_Union,
  //  CKeyword_Const,
  //  CKeyword_Short,
  //  CKeyword_Unsigned,
  //  CKeyword_Continue,
  //  CKeyword_For,
  //  CKeyword_Signed,
  //  CKeyword_Default,
  //  CKeyword_Goto,
  //  CKeyword_Sizeof,
  //  CKeyword_Volatile,
  //  CKeyword_Do,
  //  CKeyword_If,
  //  CKeyword_Static,
  //  CKeyword_While,
  //  CKeyword_Float,
  //  CKeyword_Char,
  //  CKeyword_Int,
  //  CKeyword_Bool,
  //  CKeyword_Void,
  std::string source =
      "auto struct break else long switch case enum register typedef extern "
      "return union const short unsigned continue for signed default goto "
      "sizeof volatile do if static while int bool char float void";
  Lexer lexer = Lexer(source);
  Token token = lexer.next_token();
  for (int i = 0; i < CTOKENS_NUM_KEYWORDS; i++) {
    CToken expected = CToken(i + int(CToken::CKeyword_Auto));

    if (token.type != expected) {
      std::cout << "Expected: " << int(expected) << " Got: " << int(token.type)
                << std::endl;
      FAIL();
    }

    token = lexer.next_token();
  }
}

TEST(Lexer, Operator) {
  //  COperator_Plus,
  //  COperator_Minus,
  //  COperator_Asterix,
  //  COperator_Divide,
  //  COperator_Modulus,
  //  COperator_Assignment,
  //  COperator_PlusAssignment,
  //  COperator_MinusAssignment,
  //  COperator_MultiplyAssignment,
  //  COperator_DivideAssignment,
  //  COperator_ModulusAssignment,
  //  COperator_Increment,
  //  COperator_Decrement,
  //  COperator_Equal,
  //  COperator_NotEqual,
  //  COperator_LessThan,
  //  COperator_GreaterThan,
  //  COperator_LessThanOrEqual,
  //  COperator_GreaterThanOrEqual,
  //  COperator_LogicalAnd,
  //  COperator_LogicalOr,
  //  COperator_LogicalNot,
  //  COperator_Ampersand,
  //  COperator_BitwiseOr,
  //  COperator_BitwiseNot,
  //  COperator_BitwiseXor,
  //  COperator_BitwiseLeftShift,
  //  COperator_BitwiseRightShift,
  //  COperator_BitwiseAndAssignment,
  //  COperator_BitwiseOrAssignment,
  //  COperator_BitwiseXorAssignment,
  //  COperator_BitwiseLeftShiftAssignment,
  //  COperator_BitwiseRightShiftAssignment,
  //  COperator_Ternary,
  //  COperator_Comma,
  //  COperator_Arrow,
  //  COperator_Dot,
  std::string source = "+ - * / % = += -= *= /= %= ++ -- == != < > <= >= && || "
                       "! & | ~ ^ << >> &= |= ^= <<= >>= ? , -> .";
  Lexer lexer = Lexer(source);
  CToken actual = lexer.next_token().type;

  for (int i = 0; i < CTOKENS_NUM_OPERATORS; i++) {
    CToken expected = CToken(i + int(CToken::COperator_Plus));
    if (actual != expected) {
      std::cout << "Expected: " << int(expected) << " Got: " << int(actual)
                << std::endl;
      FAIL();
    }
    actual = lexer.next_token().type;
  }
}

TEST(Lexer, Punctuation) {
  //  CPunctuation_LeftParenthesis,
  //  CPunctuation_RightParenthesis,
  //  CPunctuation_LeftBrace,
  //  CPunctuation_RightBrace,
  //  CPunctuation_LeftBracket,
  //  CPunctuation_RightBracket,
  //  CPunctuation_Comma,
  //  CPunctuation_Semicolon,
  //  CPunctuation_Colon,
  //  CPunctuation_Ellipsis,
  std::string source = "( ) [ ] { } ; : ... , # ##";
  Lexer lexer = Lexer(source);
  CToken actual = lexer.next_token().type;

  for (int i = 0; i < CTOKENS_NUM_PUNCTUATION; i++) {
    CToken expected = CToken(i + int(CToken::CPunctuation_LeftParenthesis));
    if (actual != expected) {
      std::cout << "Expected: " << int(expected) << " Got: " << int(actual)
                << std::endl;
      FAIL();
    }
    actual = lexer.next_token().type;
  }
}

TEST(Lexer, Constant) {
  //  CConstant_Integer,
  //  CConstant_Float,
  //  CConstant_Character,
  //  CConstant_String,
  std::string source = "123 123.123 'a' \"hel\nlo\"";
  Lexer lexer = Lexer(source);
  CToken actual = lexer.next_token().type;

  for (int i = 0; i < CTOKENS_NUM_CONSTANTS; i++) {
    CToken expected = CToken(i + int(CToken::CConstant_Integer));
    if (actual != expected) {
      std::cout << "Expected: " << int(expected) << " Got: " << int(actual)
                << std::endl;
      FAIL();
    }
    actual = lexer.next_token().type;
  }
}

TEST(Lexer, PreprocessorDirective) {
  //  CPreprocessorDirective_Include,
  //  CPreprocessorDirective_Define,
  //  CPreprocessorDirective_Undef,
  //  CPreprocessorDirective_If,
  //  CPreprocessorDirective_Ifdef,
  //  CPreprocessorDirective_Ifndef,
  //  CPreprocessorDirective_Elif,
  //  CPreprocessorDirective_Else,
  //  CPreprocessorDirective_Endif,
  //  CPreprocessorDirective_Error,
  std::string source = "#include #define #   undef #\tif \r\n\t\t# \r\nifdef "
                       "#ifndef #elif #else #\nendif #error";
  Lexer lexer = Lexer(source);
  CToken actual = lexer.next_token().type;

  for (int i = 0; i < CTOKENS_NUM_PREPROCESSOR_DIRECTIVES; i++) {
    CToken expected = CToken(i + int(CToken::CPreprocessorDirective_Include));
    if (actual != expected) {
      std::cout << "Expected: " << int(expected) << " Got: " << int(actual)
                << std::endl;
      FAIL();
    }
    actual = lexer.next_token().type;
  }
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
  ASSERT_EQ(token.type, CToken::CPreprocessorDirective_Include);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::COperator_LessThan);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::CIdentifier);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::COperator_Dot);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::CIdentifier);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::COperator_GreaterThan);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::CKeyword_Int);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::CIdentifier);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::CPunctuation_LeftParenthesis);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::CPunctuation_RightParenthesis);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::CPunctuation_LeftBrace);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::CIdentifier);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::CPunctuation_LeftParenthesis);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::CConstant_String);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::CPunctuation_RightParenthesis);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::CPunctuation_Semicolon);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::CKeyword_Return);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::CConstant_Integer);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::CPunctuation_Semicolon);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::CPunctuation_RightBrace);token = lexer.next_token();
  ASSERT_EQ(token.type, CToken::CEOF);
}