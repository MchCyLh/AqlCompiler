#pragma once
#include "Stmt.h"
class Extract_Stmt :
    public Stmt
{
public:
    Stmt *stmt1, *stmt2;
    Extract_Stmt() {}
    void init(Stmt *s1, Stmt *s2) { stmt1 = s1; stmt2 = s2; }

    void gen() {
        stmt2->gen();   // From_Item->gen() | From_Item_Join->gen();
        stmt1->gen();   // Regex_Spec->gen() | Pattern_Spec->gen();
    }
};

