#include <lexer.h>
#include <iostream>
#include <args.h>

bool Lexer::dealWithIncludes() {
  this->resetCursor();
  for (int i = 0; i < tokens.size(); i++) {
    if (tokens[i].type == CToken::CPreprocessorDirective_Include) {
      Token includeToken = tokens[i];
      int fname_length = 0;
      for (int j = i + 2; j < tokens.size(); j++) {
        if (tokens[j].type == CToken::COperator_GreaterThan) {
          break;
        }
        fname_length++;
      }
      std::string fname = "";
      for (int j = i + 2; j < i + 2 + fname_length; j++) {
        fname += tokens[j].value;
      }

      string fullPath = searchIncludePathsForFile(fname, includeDirs);
      if (fullPath == "") {
        std::cerr << "Could not find file: " << fname << std::endl;
        return false;
      }

      std::string fileContents = loadSourceToString(fullPath);
      Lexer *lex = new Lexer(fileContents, includeDirs);
      lex->preprocess();
      lex->tokens.pop_back(); // remove the EOF token
      tokens.erase(tokens.begin() + i, tokens.begin() + i + 2 + fname_length);
      tokens.insert(tokens.begin() + i, lex->tokens.begin(), lex->tokens.end());

      delete lex;
    }
  }

  return true;
}