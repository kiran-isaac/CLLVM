#ifndef CLLVM_PREPROCESSOR_TOKENS_H
#define CLLVM_PREPROCESSOR_TOKENS_H

#include <string>

enum class PreprocessorTokens {
  Identifier,
  Number,
  String,
  Character,
  Punctuator,
  Operator,
  Whitespace,
  Newline,
  Comment,
  PreprocessorDirective,
  EndOfFile
};

enum class PreprocessorDirective {
  PreprocessorDirective_Include, // #include
  PreprocessorDirective_Define, // #define
  PreprocessorDirective_Undef, // #undef
  PreprocessorDirective_If, // #if
  PreprocessorDirective_Ifdef, // #ifdef
  PreprocessorDirective_Ifndef, // #ifndef
};

struct Token {
  PreprocessorDirective type;
  std::string value;
};

#endif /* CLLVM_PREPROCESSOR_TOKENS_H */