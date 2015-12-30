#pragma once
#include "Stmt.h"
class Pattern_Pkg :
    public Stmt
{
public:
    Stmt *stmt1, *stmt2, *stmt3;
    Token *num1, *num2;
    Pattern_Pkg() {}
    void init(Stmt *s1, Stmt *s2, Token *t1, Token *t2, Stmt *s3) {
        stmt1 = s1;
        stmt2 = s2;
        stmt3 = s3;
        num1 = t1;
        num2 = t2;
    }
};

