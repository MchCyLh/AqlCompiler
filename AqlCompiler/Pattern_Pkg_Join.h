#ifndef PATTERN_PKG_JOIN_H
#define PATTERN_PKG_JOIN_H
#include "Stmt.h"
class Pattern_Pkg_Join :
    public Stmt
{
public:
    Stmt *stmt1, *stmt2;
    Pattern_Pkg_Join(Stmt *s1, Stmt *s2) { stmt1 = s1; stmt2 = s2; }
    ~Pattern_Pkg_Join() {
        delete stmt1; stmt1 = Stmt::Null;
        delete stmt2; stmt2 = Stmt::Null;
    }
	void gen(){
		stmt1->gen();
		stmt2->gen();
	}
};

#endif