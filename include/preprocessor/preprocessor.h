#ifndef CLLVM_PREPROCESSOR_PREPROCESSOR_H
#define CLLVM_PREPROCESSOR_PREPROCESSOR_H

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

void removeTrigraphs(std::string& source);
void removeLineSplices(std::string& source);
void removeComments(std::string& source);

void preprocess(std::string& source);

#endif /* CLLVM_PREPROCESSOR_PREPROCESSOR_H */