#ifndef CLLVM_TOKENS_H
#define CLLVM_TOKENS_H

#include <string>

enum class CKeyword {
  CKeyword_Auto,
  CKeyword_Double,
  CKeyword_Int,
  CKeyword_Struct,
  CKeyword_Break,
  CKeyword_Else,
  CKeyword_Long,
  CKeyword_Switch,
  CKeyword_Case,
  CKeyword_Enum,
  CKeyword_Register,
  CKeyword_Typedef,
  CKeyword_Char,
  CKeyword_Extern,
  CKeyword_Return,
  CKeyword_Union,
  CKeyword_Const,
  CKeyword_Float,
  CKeyword_Short,
  CKeyword_Unsigned,
  CKeyword_Continue,
  CKeyword_For,
  CKeyword_Signed,
  CKeyword_Void,
  CKeyword_Default,
  CKeyword_Goto,
  CKeyword_Sizeof,
  CKeyword_Volatile,
  CKeyword_Do,
  CKeyword_If,
  CKeyword_Static,
  CKeyword_While,
  CKeyword_Unknown
};

enum class COperator {
  COperator_Plus,
  COperator_Minus,
  COperator_Multiply,
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
  COperator_BitwiseAnd,
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
  COperator_Comma,
  COperator_Arrow,
  COperator_Dot,
  COperator_AddressOf,
  COperator_Dereference,
  COperator_Sizeof,
  COperator_Cast,
  COperator_Unknown
};

enum class CPunctuation {
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
  CPunctuation_Unknown
};

enum class CConstant {
  CConstant_Integer,
  CConstant_Float,
  CConstant_Character,
  CConstant_String,
  CConstant_Unknown
};

enum class CType {
  CType_Int,
  CType_Float,
  CType_Char,
  CType_Void,
  CType_Unknown
};

enum class CToken {
  CToken_Keyword,
  CToken_Operator,
  CToken_Punctuation,
  CToken_Identifier,
  CToken_Constant,
  CToken_Type,
  CToken_Unknown
};

union CTokenValue {
  CKeyword keyword;
  COperator op;
  CPunctuation punct;
  CConstant constant;
  CType type;
};

struct Token {
  CToken type;
  CTokenValue value;
  std::string value;
};

// int main() { return 0; } -> [int, main, (, ), {, return, 0, ;, }]

#endif /* CLLVM_TOKENS_H */
