#ifndef OUTPUT_STMT_H
#define OUTPUT_STMT_H

#include "Stmt.h"
#include "outputTable.h"
#include "TypeDefine.h"
#include "Alias.h"
// #include "outputTable.h"

class Output_Stmt :
    public Stmt
{
public:
    Token *id;
    Stmt *als;
    Output_Stmt() {}
    void init(Token *t, Stmt *s) { id = t; als = s; }

    void gen() {
        Id *name = static_cast<Id *>(id);
		string alias_name = (als == Alias::Null ? name->lexeme : (als->gen(), __alias));
        outputTable(alias_name, ntr[name->lexeme]);
    }

    void Delete() {
        delete id; id = Token::Null;
        als->Delete(); delete als; als = Stmt::Null;
    }
};

#endif