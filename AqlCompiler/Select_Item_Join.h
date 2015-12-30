#pragma once
#include "Stmt.h"
class Select_Item_Join : public Stmt
{
public:
    Stmt * stmt1, *stmt2;
    Select_Item_Join() {}
    Select_Item_Join(Stmt *s1, Stmt *s2) { stmt1 = s1; stmt2 = s2; }

    void gen() {
        stmt1->gen(); // Select_Item->gen();
        stmt2->gen(); // Select_Item_Join->gen();
    }
};
