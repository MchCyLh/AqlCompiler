#ifndef SELECT_ITEM_H
#define SELECT_ITEM_H

#include "Stmt.h"
#include "Alias.h"
class Select_Item : public Stmt
{
public:
    Token *id1, *id2;
    Stmt *a_stmt;
    Select_Item() {}
    ~Select_Item() {
        delete id1; id1 = Token::Null;
        delete id2; id2 = Token::Null;
        delete a_stmt; a_stmt = Stmt::Null;
    }
    void init(Token *t1, Token *t2, Stmt *s) { id1 = t1; id2 = t2; a_stmt = s; }
    //static Select_Item *Null;

    void gen() {
        // ø…”≈ªØ
        Id *id = static_cast<Id *>(id1); string &id1_name = id->lexeme;
        id = static_cast<Id *>(id2); string &id2_name = id->lexeme;
		string &alias_name = (a_stmt == Alias::Null ? id2_name : (a_stmt->gen(), __alias));
        vector<string> item;
        item.push_back(id1_name); item.push_back(id2_name); item.push_back(alias_name);
        __select_list.push_back(item);
    }
};


#endif