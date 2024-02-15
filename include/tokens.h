#ifndef CLLVM_TOKENS_H
#define CLLVM_TOKENS_H

#include <map>
#include <regex>
#include <string>
#include <utility>
#include <vector>

enum class CToken {
  CKeyword_Auto,
  CKeyword_Struct,
  CKeyword_Break,
  CKeyword_Else,
  CKeyword_Long,
  CKeyword_Switch,
  CKeyword_Case,
  CKeyword_Enum,
  CKeyword_Register,
  CKeyword_Typedef,
  CKeyword_Extern,
  CKeyword_Return,
  CKeyword_Union,
  CKeyword_Const,
  CKeyword_Short,
  CKeyword_Unsigned,
  CKeyword_Continue,
  CKeyword_For,
  CKeyword_Signed,
  CKeyword_Default,
  CKeyword_Goto,
  CKeyword_Sizeof,
  CKeyword_Volatile,
  CKeyword_Do,
  CKeyword_If,
  CKeyword_Static,
  CKeyword_While,
  CKeyword_Float,
  CKeyword_Char,
  CKeyword_Int,
  CKeyword_Bool,
  CKeyword_Void,

  CIdentifier,

  COperator_Plus,
  COperator_Minus,
  COperator_Asterix,
  COperator_Divide,
  COperator_Modulus,
  COperator_Assignment,
  COperator_PlusAssignment,
  COperator_MinusAssignment,
  COperator_MultiplyAssignment,
  COperator_DivideAssignment,
  COperator_ModulusAssignment,
  COperator_Increment,
  COperator_Decrement,
  COperator_Equal,
  COperator_NotEqual,
  COperator_LessThan,
  COperator_GreaterThan,
  COperator_LessThanOrEqual,
  COperator_GreaterThanOrEqual,
  COperator_LogicalAnd,
  COperator_LogicalOr,
  COperator_LogicalNot,
  COperator_Ampersand,
  COperator_BitwiseOr,
  COperator_BitwiseNot,
  COperator_BitwiseXor,
  COperator_BitwiseLeftShift,
  COperator_BitwiseRightShift,
  COperator_BitwiseAndAssignment,
  COperator_BitwiseOrAssignment,
  COperator_BitwiseXorAssignment,
  COperator_BitwiseLeftShiftAssignment,
  COperator_BitwiseRightShiftAssignment,
  COperator_Ternary,
  COperator_Arrow,
  COperator_Dot,

  CPunctuation_LeftParenthesis,
  CPunctuation_RightParenthesis,
  CPunctuation_LeftBrace,
  CPunctuation_RightBrace,
  CPunctuation_LeftBracket,
  CPunctuation_RightBracket,
  CPunctuation_Comma,
  CPunctuation_Semicolon,
  CPunctuation_Colon,
  CPunctuation_Ellipsis,

  CConstant_Integer,
  CConstant_Float,
  CConstant_Character,
  CConstant_String,

  CPreprocessorDirective_Include,
  CPreprocessorDirective_Define,
  CPreprocessorDirective_Undef,
  CPreprocessorDirective_If,
  CPreprocessorDirective_Ifdef,
  CPreprocessorDirective_Ifndef,
  CPreprocessorDirective_Elif,
  CPreprocessorDirective_Else,
  CPreprocessorDirective_Endif,
  CPreprocessorDirective_Error,

  CEOF = -1,
  CUnknown = -2,
};

#define CTOKENS_NUM_KEYWORDS                                                   \
  int(CToken::CKeyword_While) - int(CToken::CKeyword_Auto) + 1
#define CTOKENS_NUM_OPERATORS                                                  \
  int(CToken::COperator_Dot) - int(CToken::COperator_Plus) + 1
#define CTOKENS_NUM_PUNCTUATION                                                \
  int(CToken::CPunctuation_Ellipsis) -                                         \
      int(CToken::CPunctuation_LeftParenthesis) + 1
#define CTOKENS_NUM_CONSTANTS                                                  \
  int(CToken::CConstant_String) - int(CToken::CConstant_Integer) + 1
#define CTOKENS_NUM_TYPES int(CToken::CType_Void) - int(CToken::CType_Int) + 1
#define CTOKENS_NUM_PREPROCESSOR_DIRECTIVES                                    \
  int(CToken::CPreprocessorDirective_Error) -                                  \
      int(CToken::CPreprocessorDirective_Include) + 1

class Token {
public:
  CToken type;
  std::string value;

  Token(CToken type, std::string value);
};

using std::map, std::string, std::vector, std::pair, std::regex;

static vector<pair<CToken, string>> tokenRegexMap = {
    {CToken::CKeyword_Auto, "auto"},
    {CToken::CKeyword_Struct, "struct"},
    {CToken::CKeyword_Break, "break"},
    {CToken::CKeyword_Else, "else"},
    {CToken::CKeyword_Long, "long"},
    {CToken::CKeyword_Switch, "switch"},
    {CToken::CKeyword_Case, "case"},
    {CToken::CKeyword_Enum, "enum"},
    {CToken::CKeyword_Register, "register"},
    {CToken::CKeyword_Typedef, "typedef"},
    {CToken::CKeyword_Extern, "extern"},
    {CToken::CKeyword_Return, "return"},
    {CToken::CKeyword_Union, "union"},
    {CToken::CKeyword_Const, "const"},
    {CToken::CKeyword_Short, "short"},
    {CToken::CKeyword_Unsigned, "unsigned"},
    {CToken::CKeyword_Continue, "continue"},
    {CToken::CKeyword_For, "for"},
    {CToken::CKeyword_Signed, "signed"},
    {CToken::CKeyword_Default, "default"},
    {CToken::CKeyword_Goto, "goto"},
    {CToken::CKeyword_Sizeof, "sizeof"},
    {CToken::CKeyword_Volatile, "volatile"},
    {CToken::CKeyword_Do, "do"},
    {CToken::CKeyword_If, "if"},
    {CToken::CKeyword_Static, "static"},
    {CToken::CKeyword_While, "while"},
    {CToken::CKeyword_Int, "int"},
    {CToken::CKeyword_Bool, "bool"},
    {CToken::CKeyword_Char, "char"},
    {CToken::CKeyword_Float, "float"},
    {CToken::CKeyword_Void, "void"},

    {CToken::CIdentifier, "[a-zA-Z_][a-zA-Z0-9_]*"},

    {CToken::CPunctuation_LeftParenthesis, "\\("},
    {CToken::CPunctuation_RightParenthesis, "\\)"},
    {CToken::CPunctuation_LeftBrace, "\\{"},
    {CToken::CPunctuation_RightBrace, "\\}"},
    {CToken::CPunctuation_LeftBracket, "\\["},
    {CToken::CPunctuation_RightBracket, "\\]"},
    {CToken::CPunctuation_Comma, ","},
    {CToken::CPunctuation_Semicolon, ";"},
    {CToken::CPunctuation_Colon, ":"},
    {CToken::CPunctuation_Ellipsis, "\\.{3}"},

    {CToken::COperator_PlusAssignment, "\\+="},
    {CToken::COperator_MinusAssignment, "-="},
    {CToken::COperator_MultiplyAssignment, "\\*="},
    {CToken::COperator_DivideAssignment, "/="},
    {CToken::COperator_ModulusAssignment, "%="},
    {CToken::COperator_Increment, "\\+\\+"},
    {CToken::COperator_Decrement, "--"},
    {CToken::COperator_Equal, "=="},
    {CToken::COperator_NotEqual, "!="},
    {CToken::COperator_LessThanOrEqual, "<="},
    {CToken::COperator_GreaterThanOrEqual, ">="},
    {CToken::COperator_LogicalAnd, "&&"},
    {CToken::COperator_LogicalOr, "\\|\\|"},
    {CToken::COperator_BitwiseAndAssignment, "&="},
    {CToken::COperator_BitwiseOrAssignment, "\\|="},
    {CToken::COperator_BitwiseXorAssignment, "\\^="},
    {CToken::COperator_BitwiseLeftShiftAssignment, "<<="},
    {CToken::COperator_BitwiseRightShiftAssignment, ">>="},
    {CToken::COperator_Ternary, "\\?"},
    {CToken::COperator_Arrow, "->"},
    {CToken::COperator_Dot, "\\."},
    {CToken::COperator_Plus, "\\+"},
    {CToken::COperator_Minus, "-"},
    {CToken::COperator_Asterix, "\\*"},
    {CToken::COperator_Divide, "/"},
    {CToken::COperator_Modulus, "%"},
    {CToken::COperator_Assignment, "="},
    {CToken::COperator_LogicalNot, "!"},
    {CToken::COperator_Ampersand, "&"},
    {CToken::COperator_BitwiseOr, "\\|"},
    {CToken::COperator_BitwiseNot, "~"},
    {CToken::COperator_BitwiseXor, "\\^"},
    {CToken::COperator_BitwiseLeftShift, "<<"},
    {CToken::COperator_BitwiseRightShift, ">>"},
    {CToken::COperator_LessThan, "<"},
    {CToken::COperator_GreaterThan, ">"},

    {CToken::CConstant_Float, "\\d+\\.\\d+"},
    {CToken::CConstant_Integer, "\\d+"},
    {CToken::CConstant_String, "\"((\\n|\\t|\\r|\\v|\\f|\\b|\\a|\\\\|\\?|\\'|\\\")|.)*\""},
    {CToken::CConstant_Character, "'((\\n|\\t|\\r|\\v|\\f|\\b|\\a|\\\\|\\?|\\'|\\\")|.)'"},

    {CToken::CPreprocessorDirective_Include, "#[ \r\t\n]*include"},
    {CToken::CPreprocessorDirective_Define, "#[ \r\t\n]*define"},
    {CToken::CPreprocessorDirective_Undef, "#[ \r\t\n]*undef"},
    {CToken::CPreprocessorDirective_Ifndef, "#[ \r\t\n]*ifndef"},
    {CToken::CPreprocessorDirective_Ifdef, "#[ \r\t\n]*ifdef"},
    {CToken::CPreprocessorDirective_If, "#[ \r\t\n]*if"},
    {CToken::CPreprocessorDirective_Elif, "#[ \r\t\n]*elif"},
    {CToken::CPreprocessorDirective_Else, "#[ \r\t\n]*else"},
    {CToken::CPreprocessorDirective_Endif, "#[ \r\t\n]*endif"},
    {CToken::CPreprocessorDirective_Error, "#[ \r\t\n]*error"}};

// int main() { return 0; } -> [int, main, (, ), {, return, 0, ;, }]

#endif /* CLLVM_TOKENS_H */
