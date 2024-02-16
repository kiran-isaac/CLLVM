#include <lexer.h>

void Lexer::removeTrigraphs() {
  std::string trigraphs[] = {"??=", "??/", "??'", "??(", "??)",
                             "??!", "??<", "??>", "??-", "??!"};
  std::string replacements[] = {"#", "\\", "^", "[", "]",
                                "|", "{",  "}", "~", "!"};

  for (int i = 0; i < 10; i++) {
    size_t pos = source.find(trigraphs[i]);
    while (pos != std::string::npos) {
      source.replace(pos, 3, replacements[i]);
      pos = source.find(trigraphs[i]);
    }
  }
}

void Lexer::removeLineSplices() {
  this->resetCursor();
  size_t first_token_index = 0;
  Token tk = next_token();
  Token tk2 = next_token();
  while (tk.type != CToken::CEOF) {
    if (tk.type == CToken::CLineSplice && tk2.type == CToken::CNewline) {
      tokens.erase(tokens.begin() + findIndexOfTokenWithID(tk.id));
      tokens.erase(tokens.begin() + findIndexOfTokenWithID(tk2.id));

      // Add a space to the beginning of the next tokens value
      tokens[first_token_index].value = " " + tokens[first_token_index].value;

      tk = tokens[first_token_index];
      tk2 = tokens[first_token_index + 1];
    } else {
      first_token_index++;
      tk = tk2;
      tk2 = next_token();
    }
  }
}

void Lexer::removeSingleLineComments() {
  this->resetCursor();
  size_t first_token_index = 0;
  Token tk = next_token();

  while (tk.type != CToken::CEOF) {
    if (tk.type == CToken::CComment) {
      tokens.erase(tokens.begin() + findIndexOfTokenWithID(tk.id));
      tk = tokens[first_token_index];
    } else {
      first_token_index++;
      tk = next_token();
    }
  }
}

void Lexer::removeMultiLineComments() {
  this->resetCursor();
  size_t first_token_index = 0;
  Token tk = next_token();

  while (tk.type != CToken::CEOF) {
    if (tk.type == CToken::CMultilineComment) {
      tokens.erase(tokens.begin() + findIndexOfTokenWithID(tk.id));
      tk = tokens[first_token_index];
    } else {
      first_token_index++;
      tk = next_token();
    }
  }
}

string Lexer::stripWhitespace(const std::string &input) {
  std::string output = "";
  // remove leading whitespace
  size_t start = input.find_first_not_of(" \t");
  if (start != std::string::npos) {
    output = input.substr(start);
  }

  // remove trailing whitespace
  size_t end = output.find_last_not_of(" \t");
  if (end != std::string::npos) {
    output = output.substr(0, end + 1);
  }

  return output;
}

void Lexer::preprocess() {
  removeLineSplices();
  removeSingleLineComments();
  removeMultiLineComments();

  resetCursor();
}