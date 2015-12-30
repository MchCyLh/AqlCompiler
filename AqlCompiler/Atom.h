#pragma once
#include "Stmt.h"
#include "Token.h"

class Atom :
    public Stmt
{
public:
    Stmt *s; Token *reg;
    Atom() {}
    void init(Stmt *s_, Token *t) { s = s_; reg = t; }
};

