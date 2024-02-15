#ifndef CLLVM_LEXER_H
#define CLLVM_LEXER_H

#include <lexer.h>
#include <tokens.h>

class Lexer {
public:
  int index;
  std::string source;

  Lexer(std::string source);
  Token next_token();
};

#endif /* CLLVM_LEXER_H */