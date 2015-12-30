#pragma once
#include "Stmt.h"
#include "Token.h"

class Name_Spec :
    public Stmt
{
public:
    Token *id;
    Stmt *s;
    Name_Spec() {}
    void init(Token *t) { id = t; s = Stmt::Null; }
    void init(Stmt *s_) { s = s_; id = Token::Null; }
	void gen() {
		if (id == Token::Null) {
			s->gen(); // Single_Group->gen() | Single_Group_Join->gen()
		}
		else {
			Id *id_name = static_cast<Id *>(id);
			string &name = id_name->lexeme;
			__groups[0] = name;
		}
	}
};

