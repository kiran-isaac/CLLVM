#ifndef CLLVM_PREPROCESSOR_PREPROCESSOR_H
#define CLLVM_PREPROCESSOR_PREPROCESSOR_H

#include <string>
#include <regex>

void removeTrigraphs(std::string& source);
void removeLineSplices(std::string& source);
void removeComments(std::string& source);

void pre_tokenization_processing(std::string& source);

#endif /* CLLVM_PREPROCESSOR_PREPROCESSOR_H */