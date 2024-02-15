#include <lexer.h>
#include <tokens.h>
#include <algorithm>
#include <cctype>
#include <string>

Token::Token(CToken type, std::string value) {
  this->type = type;
  this->value = value;
}

Lexer::Lexer(std::string source) {
  this->source = source;
  this->index = 0;
}

std::string stripWhitespace(const std::string& input) {
  std::string output = input;
  output.erase(std::remove_if(output.begin(), output.end(), ::isspace), output.end());
  return output;
}

Token Lexer::next_token() {
  // use the regular expressions in the tokens.h file to match the next token
  // in the source code

  for (int i = this->index; i < this->source.length() - 1; i++) {
    for (auto const& [key, val] : tokenRegexMap) {
      std::regex e("^[ \r\t\n]*" + val);
      std::smatch m;
      std::string s = this->source.substr(i);
      if (std::regex_search(s, m, e) && m.position() == 0) {
        this->index = i + m.length();
        string str = stripWhitespace(m.str());
        return Token(key, str);
      }
    }
  }

  if (this->index == this->source.length()) {
    return Token(CToken::CEOF, "");
  }

  return Token(CToken::CUnknown, "");
}