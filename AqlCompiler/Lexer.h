#ifndef LEXER_H
#define LEXER_H

#include<iostream>
#include<vector>
#include<string>
#include "Token.h"
#include<fstream>
#include "Num.h"
#include "Word.h"
using namespace std;

class Lexer {
public:
	Lexer(string file_path);
	Token* scan();
    ~Lexer() {
        fin.close();
    }
private:
	int row = 0;
	int col = -1;
	ifstream fin;
	int is_regex = 0;
};

int choose_type(string temp);

#endif