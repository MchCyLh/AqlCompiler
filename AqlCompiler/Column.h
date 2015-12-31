#ifndef COLUMN_H
#define COLUMN_H
#include "Stmt.h"
#include "Token.h"
class Column :
    public Stmt
{
public:
    Token *id1, *id2;
    Column() {}
    void init(Token *t1, Token *t2) { id1 = t1; id2 = t2; }
	void gen() {
		Id * id = static_cast<Id *>(id1);
		__column.first = id->lexeme;
		id = static_cast<Id *>(id2);
		__column.second = id->lexeme;
	}

    void Delete() {
        delete id1; id1 = Token::Null;
        delete id2; id2 = Token::Null;
    }
};

#endif