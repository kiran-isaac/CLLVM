#ifndef CLLVM_LEXER_H
#define CLLVM_LEXER_H

#include <lexer.h>
#include <tokens.h>

class Lexer {
public:
    Lexer(std::string source);

    Token next_token();

    void resetCursor() { tokenCursor = 0; }

    void preprocess();

    bool substituteTokens(vector<Token> before, vector<Token> after);

    string *getSource() { return &source; }

    string sourceFromTokens();
private:
    int line = 1;
    int column = 1;
    int index = 0;
    int currentTokenID = 0;
    std::string source;

    void removeTrigraphs();

    void removeLineSplices();

    void removeSingleLineComments();

    int findIndexOfTokenWithID(int id);

    bool generateToken();

    vector<Token> tokens;
    int tokenCursor = 0;

    string stripWhitespace(const std::string &input);

    void removeMultiLineComments();
};

#endif /* CLLVM_LEXER_H */