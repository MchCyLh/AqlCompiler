#pragma once
#include "Stmt.h"
class Single_Group :
    public Stmt
{
public:
    Token *num, *id;
    Single_Group() {}
    void init(Token *t1, Token *t2) { num = t1; id = t2; }
	void gen() {
		Num *num1 = static_cast<Num *>(num);
		Id *id1 = static_cast<Id *>(id);
		__groups[num1->value] = id1->lexeme;
	}
};

