#ifndef WORD_H
#define WORD_H
#include "Token.h"
#include <string>
using std::string;

class Word :
    public Token
{
public:
    string lexeme = "";
    Word(string s, int tag) : Token(tag), lexeme(s) {}
};

typedef Word Id;
typedef Word Reg;

#endif