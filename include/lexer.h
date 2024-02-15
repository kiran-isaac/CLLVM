#ifndef CLLVM_LEXER_H
#define CLLVM_LEXER_H

#include <lexer.h>
#include <tokens.h>

class Lexer {
public:
  Lexer(std::string source);
  Token next_token();
  void resetCursor() { tokenCursor = 0; }
private:
  int index = 0;
  std::string source;

  bool generateToken();
  vector<Token> tokens;
  int tokenCursor = 0;
  std::string stripWhitespace(const std::string& input);
};

#endif /* CLLVM_LEXER_H */