#pragma once
#include "Stmt.h"
class Pattern_Spec :
    public Stmt
{
public:
    Stmt *stmt1, *stmt2;
    Pattern_Spec() {}
    void init(Stmt *s1, Stmt *s2) { stmt1 = s1; stmt2 = s2; }
};

