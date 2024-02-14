#ifndef CLLVM_PREPROCESSOR_H
#define CLLVM_PREPROCESSOR_H

#include <string>

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

std::string removeTrigraphs(const std::string& source);

#endif /* CLLVM_PREPROCESSOR_H */