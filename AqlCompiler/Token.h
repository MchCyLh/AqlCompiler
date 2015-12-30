#pragma once

#include <iostream>
#include <string>
#include "Tag.h"


using namespace std;

class Token {
public:
	Token();
	Token(int t) { tag = t; }
	Token(string temp1, int temp2, int temp3);
	void setToken(string temp1, int temp2, int temp3);
	void setToken(string temp1);
	void set_time(int a, int b);
	void setType(int ty);
	string get_token();
	int get_start_num();
	int get_stop_num();
	int get_type();

    int tag = 271;

    static Token *Null;
private:
	string token;
	int start = 0;
	int stop = 0;
};

