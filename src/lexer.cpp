#include <algorithm>
#include <cctype>
#include <lexer.h>
#include <string>
#include <tokens.h>

Lexer::Lexer(std::string source) {
  this->source = source;
  this->index = 0;

  removeTrigraphs();
}

Lexer::Lexer(std::string source, Args *args) {
  this->source = source;
  this->index = 0;
  this->includeDirs = args->includePaths;

  removeTrigraphs();
}


bool Lexer::generateToken() {
  // use the regular expressions in the tokens.h file to match the next token
  // in the source code

  for (int i = this->index; i < this->source.length(); i++) {
    std::string s = this->source.substr(i);
    for (auto const &[key, val] : tokenRegexMap) {
      std::regex e;

      e = std::regex(val);

      std::smatch m;
      if (std::regex_search(s, m, e) && m.position() == 0) {
        this->index = i + m.length();
        string str = m.str();

        if (key == CToken::CNewline) {
          line++;
          this->tokens.push_back(Token(key, str, line, column, currentTokenID++));
          column = 1;
        } else {
          // add the amount of head whitespace to the column
          int precedingWhitespaceLength = str.find_first_not_of(" \t");
          this->tokens.push_back(Token(key, str, line, column + precedingWhitespaceLength, currentTokenID++));
          column += m.length();
        }

        return true;
      }
    }
  }

  if (this->index == this->source.length()) {
    this->tokens.push_back(Token(CToken::CEOF, "EOF", line, column));
    return true;
  }

  return false;
}

Token Lexer::next_token() {
  while (this->tokenCursor >= this->tokens.size()) {
    generateToken();
  }

  Token tk = this->tokens[this->tokenCursor++];
  return tk;
}

int Lexer::findIndexOfTokenWithID(int id) {
  // use binary search as the ids will be in order

  size_t tokens_length = this->tokens.size();
  size_t left = 0;
  size_t right = tokens_length - 1;
  size_t mid = right / 2;

  while (left <= right) {
    if (this->tokens[mid].id == id) {
      return mid;
    } else if (this->tokens[mid].id < id) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
    mid = (left + right) / 2;
  }
  return -1;
}

bool Lexer::substituteTokens(vector<Token> before, vector<Token> after) {
  for (Token tk : before) {
    int index = findIndexOfTokenWithID(tk.id);
    if (index != -1) {
      this->tokens[index] = after[0];
      for (int i = 1; i < after.size(); i++) {
        this->tokens.insert(this->tokens.begin() + index + i, after[i]);
      }
    } else {
      return false;
    }
  }

  return true;
}

std::string Lexer::sourceFromTokens() {
  std::string produced_source = "";
  for (Token tk : tokens) {
    if (tk.type == CToken::CEOF) {
      break;
    }
    produced_source += stripWhitespace(tk.value) + " ";
  }
  // remove the trailing space
  produced_source.pop_back();
  return produced_source;
}