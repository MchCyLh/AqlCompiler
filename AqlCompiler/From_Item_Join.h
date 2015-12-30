#pragma once
#include "Stmt.h"
class From_Item_Join : public Stmt
{
public:
    Stmt *stmt1, *stmt2;
    From_Item_Join(Stmt *s1, Stmt * s2) { stmt1 = s1; stmt2 = s2; }

    void gen() {
        stmt1->gen(); // From_Item->gen();
        stmt2->gen(); // From_Item_Join->gen();
    }
};

