#ifndef NUM_H
#define NUM_H

#include "Token.h"
#include "Tag.h"
class Num :
    public Token
{
public:
    int value;
    Num(int v) : Token(Tag::NUM), value(v) {}
	~Num() {}
	/*string tostr(){
		string ans;
		string temp;
		int x = value;
		while (x>0){
			temp.push_back('0' + x % 10);
			x /= 10;
		}
		for (int i = temp.size() - 1; i >= 0; i--){
			ans.push_back(temp[i]);
		}
		return ans;
	}*/
};

#endif