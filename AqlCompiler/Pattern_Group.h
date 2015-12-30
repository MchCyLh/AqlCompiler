#pragma once
#include "Stmt.h"
class Pattern_Group :
    public Stmt
{
public:
    Stmt *s;
    Pattern_Group() {}
    void init(Stmt * s_) { s = s_; }
};

