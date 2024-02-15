#include <algorithm>
#include <cctype>
#include <lexer.h>
#include <string>
#include <tokens.h>

Lexer::Lexer(std::string source) {
  this->source = source;
  this->index = 0;
}

std::string Lexer::stripWhitespace(const std::string &input) {
  std::string output = input;
  output.erase(std::remove_if(output.begin(), output.end(), ::isspace),
               output.end());
  return output;
}

bool Lexer::generateToken() {
  // use the regular expressions in the tokens.h file to match the next token
  // in the source code

  for (int i = this->index; i < this->source.length(); i++) {
    std::string s = this->source.substr(i);
    for (auto const &[key, val] : tokenRegexMap) {
      std::regex e(val);
      std::smatch m;
      if (std::regex_search(s, m, e) && m.position() == 0) {
        this->index = i + m.length();
        string str = m.str();

        if (key == CToken::CNewline) {
          line++;
          this->tokens.push_back(Token(key, str, line, column));
          column = 1;
        } else {
          // add the amount of head whitespace to the column
          int precedingWhitespaceLength = str.find_first_not_of(" \t");
          this->tokens.push_back(Token(key, str, line, column + precedingWhitespaceLength));
          column += m.length();
        }

        return true;
      }
    }
  }

  if (this->index == this->source.length()) {
    this->tokens.push_back(Token(CToken::CEOF, "", line, column));
    return true;
  }

  return false;
}

Token Lexer::next_token() {
  while (this->tokenCursor >= this->tokens.size()) {
    generateToken();
  }

  return this->tokens[this->tokenCursor++];
}