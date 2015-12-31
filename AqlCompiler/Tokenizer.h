#ifndef TOKENIZER_H
#define TOKENIZER_H

#include<iostream>
#include<string>
#include "Token.h"
#include<vector>
#include<fstream>
#include "Num.h"
#include "Word.h"
using namespace std;

class Tokenizer {
public:
	Tokenizer(string file_path);
	~Tokenizer();
	//Token next();
	//Token* scan();
	//int get_size();
	vector< pair<int, int> > & get_vector();
    int get_token_num(int left, int right);
private:
	//int number = 0;
	int size = 1;
	int left_num = -1;
	//int right_num;
	//string file;
	ifstream fin;
	vector< pair<int, int> > token_num;
};

#endif