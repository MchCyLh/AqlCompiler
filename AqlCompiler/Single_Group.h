#pragma once
#include "Stmt.h"
class Single_Group :
    public Stmt
{
public:
    Token *num, *id;
    Single_Group() {}
    void init(Token *t1, Token *t2) { num = t1; id = t2; }
};

