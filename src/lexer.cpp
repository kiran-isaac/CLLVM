#include <algorithm>
#include <cctype>
#include <lexer.h>
#include <string>
#include <tokens.h>

Token::Token(CToken type, std::string value) {
  this->type = type;
  this->value = value;
}

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
        string str = stripWhitespace(m.str());
        this->tokens.push_back(Token(key, str));
        return true;
      }
    }
  }

  if (this->index == this->source.length()) {
    this->tokens.push_back(Token(CToken::CEOF, ""));
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