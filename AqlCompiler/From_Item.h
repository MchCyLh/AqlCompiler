#ifndef FROM_ITEM_H
#define FROM_ITEM_H

#include "Stmt.h"
#include "Token.h"
#include "Word.h"
#include "TypeDefine.h"
#include <string>
using namespace std;

class From_Item : public Stmt
{
public:
    Token *id1, *id2;
    From_Item() {}
    ~From_Item() {
        delete id1; id1 = Token::Null;
        delete id2; id2 = Token::Null;
    }
    void init(Token *t1, Token *t2) { id1 = t1; id2 = t2; }
    //static From_Item *Null;

    void gen() {
        Id *id = static_cast<Id *>(id1);
        string &id1_name = id->lexeme;
        id = static_cast<Id *>(id2);
        string id2_name = id->lexeme;
        __from_list.insert(make_pair(id2_name, id1_name));
    }

};

#endif
