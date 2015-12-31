#ifndef CREATE_STMT_H
#define CREATE_STMT_H


#include "Stmt.h"
#include "Word.h"
#include "Select_Stmt.h"
#include "Extract_Stmt.h"
#include "TypeDefine.h"

class Create_Stmt : public Stmt
{
public:
    Token *t;
    Stmt *v_stmt;
    Create_Stmt() {}
    ~Create_Stmt() {
        delete t; t = Token::Null;
        delete v_stmt; v_stmt = Stmt::Null;
    }
    void init(Token *t_, Stmt *s) {
        t = t_;
        v_stmt = s;
    }

    void gen() {
        Id * id = static_cast<Id *>(t);
        string &table_name = id->lexeme;
        v_stmt->gen();  // Select_Stmt->gen() | Extract_Stmt->gen();
        ntr.insert(make_pair(table_name, __target_table));
    }

};

#endif