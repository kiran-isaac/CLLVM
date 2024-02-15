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

  CPunctuation_newline,
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
    {CToken::CPunctuation_newline, "^[ \r\t]*\\n"},

    {CToken::CKeyword_Auto, "^[ \r\t\n]*auto"},
    {CToken::CKeyword_Struct, "^[ \r\t\n]*struct"},
    {CToken::CKeyword_Break, "^[ \r\t\n]*break"},
    {CToken::CKeyword_Else, "^[ \r\t\n]*else"},
    {CToken::CKeyword_Long, "^[ \r\t\n]*long"},
    {CToken::CKeyword_Switch, "^[ \r\t\n]*switch"},
    {CToken::CKeyword_Case, "^[ \r\t\n]*case"},
    {CToken::CKeyword_Enum, "^[ \r\t\n]*enum"},
    {CToken::CKeyword_Register, "^[ \r\t\n]*register"},
    {CToken::CKeyword_Typedef, "^[ \r\t\n]*typedef"},
    {CToken::CKeyword_Extern, "^[ \r\t\n]*extern"},
    {CToken::CKeyword_Return, "^[ \r\t\n]*return"},
    {CToken::CKeyword_Union, "^[ \r\t\n]*union"},
    {CToken::CKeyword_Const, "^[ \r\t\n]*const"},
    {CToken::CKeyword_Short, "^[ \r\t\n]*short"},
    {CToken::CKeyword_Unsigned, "^[ \r\t\n]*unsigned"},
    {CToken::CKeyword_Continue, "^[ \r\t\n]*continue"},
    {CToken::CKeyword_For, "^[ \r\t\n]*for"},
    {CToken::CKeyword_Signed, "^[ \r\t\n]*signed"},
    {CToken::CKeyword_Default, "^[ \r\t\n]*default"},
    {CToken::CKeyword_Goto, "^[ \r\t\n]*goto"},
    {CToken::CKeyword_Sizeof, "^[ \r\t\n]*sizeof"},
    {CToken::CKeyword_Volatile, "^[ \r\t\n]*volatile"},
    {CToken::CKeyword_Do, "^[ \r\t\n]*do"},
    {CToken::CKeyword_If, "^[ \r\t\n]*if"},
    {CToken::CKeyword_Static, "^[ \r\t\n]*static"},
    {CToken::CKeyword_While, "^[ \r\t\n]*while"},
    {CToken::CKeyword_Int, "^[ \r\t\n]*int"},
    {CToken::CKeyword_Bool, "^[ \r\t\n]*bool"},
    {CToken::CKeyword_Char, "^[ \r\t\n]*char"},
    {CToken::CKeyword_Float, "^[ \r\t\n]*float"},
    {CToken::CKeyword_Void, "^[ \r\t\n]*void"},
    {CToken::CIdentifier, "^[ \r\t\n]*[a-zA-Z_][a-zA-Z0-9_]*"},

    {CToken::CPunctuation_LeftParenthesis, "^[ \r\t\n]*\\("},
    {CToken::CPunctuation_RightParenthesis, "^[ \r\t\n]*\\)"},
    {CToken::CPunctuation_LeftBrace, "^[ \r\t\n]*\\{"},
    {CToken::CPunctuation_RightBrace, "^[ \r\t\n]*\\}"},
    {CToken::CPunctuation_LeftBracket, "^[ \r\t\n]*\\["},
    {CToken::CPunctuation_RightBracket, "^[ \r\t\n]*\\]"},
    {CToken::CPunctuation_Comma, "^[ \r\t\n]*,"},
    {CToken::CPunctuation_Semicolon, "^[ \r\t\n]*;"},
    {CToken::CPunctuation_Colon, "^[ \r\t\n]*:"},
    {CToken::CPunctuation_Ellipsis, "^[ \r\t\n]*\\.{3}"},

    {CToken::COperator_PlusAssignment, "^[ \r\t\n]*\\+="},
    {CToken::COperator_MinusAssignment, "^[ \r\t\n]*-="},
    {CToken::COperator_MultiplyAssignment, "^[ \r\t\n]*\\*="},
    {CToken::COperator_DivideAssignment, "^[ \r\t\n]*/="},
    {CToken::COperator_ModulusAssignment, "^[ \r\t\n]*%="},
    {CToken::COperator_Increment, "^[ \r\t\n]*\\+\\+"},
    {CToken::COperator_Decrement, "^[ \r\t\n]*--"},
    {CToken::COperator_Equal, "^[ \r\t\n]*=="},
    {CToken::COperator_NotEqual, "^[ \r\t\n]*!="},
    {CToken::COperator_LessThanOrEqual, "^[ \r\t\n]*<="},
    {CToken::COperator_GreaterThanOrEqual, "^[ \r\t\n]*>="},
    {CToken::COperator_LogicalAnd, "^[ \r\t\n]*&&"},
    {CToken::COperator_LogicalOr, "^[ \r\t\n]*\\|\\|"},
    {CToken::COperator_BitwiseAndAssignment, "^[ \r\t\n]*&="},
    {CToken::COperator_BitwiseOrAssignment, "^[ \r\t\n]*\\|="},
    {CToken::COperator_BitwiseXorAssignment, "^[ \r\t\n]*\\^="},
    {CToken::COperator_BitwiseLeftShiftAssignment, "^[ \r\t\n]*<<="},
    {CToken::COperator_BitwiseRightShiftAssignment, "^[ \r\t\n]*>>="},
    {CToken::COperator_Ternary, "^[ \r\t\n]*\\?"},
    {CToken::COperator_Arrow, "^[ \r\t\n]*->"},
    {CToken::COperator_Dot, "^[ \r\t\n]*\\."},
    {CToken::COperator_Plus, "^[ \r\t\n]*\\+"},
    {CToken::COperator_Minus, "^[ \r\t\n]*-"},
    {CToken::COperator_Asterix, "^[ \r\t\n]*\\*"},
    {CToken::COperator_Divide, "^[ \r\t\n]*/"},
    {CToken::COperator_Modulus, "^[ \r\t\n]*%"},
    {CToken::COperator_Assignment, "^[ \r\t\n]*="},
    {CToken::COperator_LogicalNot, "^[ \r\t\n]*!"},
    {CToken::COperator_Ampersand, "^[ \r\t\n]*&"},
    {CToken::COperator_BitwiseOr, "^[ \r\t\n]*\\|"},
    {CToken::COperator_BitwiseNot, "^[ \r\t\n]*~"},
    {CToken::COperator_BitwiseXor, "^[ \r\t\n]*\\^"},
    {CToken::COperator_BitwiseLeftShift, "^[ \r\t\n]*<<"},
    {CToken::COperator_BitwiseRightShift, "^[ \r\t\n]*>>"},
    {CToken::COperator_LessThan, "^[ \r\t\n]*<"},
    {CToken::COperator_GreaterThan, "^[ \r\t\n]*>"},

    {CToken::CConstant_Float, "^[ \r\t\n]*\\d+\\.\\d+"},
    {CToken::CConstant_Integer, "^[ \r\t\n]*\\d+"},
    {CToken::CConstant_String, "^[ \r\t\n]*\"((\\n|\\t|\\r|\\v|\\f|\\b|\\a|\\\\|\\?|\\'|\\\")|.)*\""},
    {CToken::CConstant_Character, "^[ \r\t\n]*'((\\n|\\t|\\r|\\v|\\f|\\b|\\a|\\\\|\\?|\\'|\\\")|.)'"},

    {CToken::CPreprocessorDirective_Include, "^[ \r\t\n]*#[ \r\t\n]*include"},
    {CToken::CPreprocessorDirective_Define, "^[ \r\t\n]*#[ \r\t\n]*define"},
    {CToken::CPreprocessorDirective_Undef, "^[ \r\t\n]*#[ \r\t\n]*undef"},
    {CToken::CPreprocessorDirective_Ifndef, "^[ \r\t\n]*#[ \r\t\n]*ifndef"},
    {CToken::CPreprocessorDirective_Ifdef, "^[ \r\t\n]*#[ \r\t\n]*ifdef"},
    {CToken::CPreprocessorDirective_If, "^[ \r\t\n]*#[ \r\t\n]*if"},
    {CToken::CPreprocessorDirective_Elif, "^[ \r\t\n]*#[ \r\t\n]*elif"},
    {CToken::CPreprocessorDirective_Else, "^[ \r\t\n]*#[ \r\t\n]*else"},
    {CToken::CPreprocessorDirective_Endif, "^[ \r\t\n]*#[ \r\t\n]*endif"},
    {CToken::CPreprocessorDirective_Error, "^[ \r\t\n]*#[ \r\t\n]*error"}
};

// int main() { return 0; } -> [int, main, (, ), {, return, 0, ;, }]

#endif /* CLLVM_TOKENS_H */
