#ifndef SINGLE_GROUP_JOIN_H
#define SINGLE_GROUP_JOIN_H

#include "Stmt.h"
class Single_Group_Join :
    public Stmt
{
public:
    Stmt *stmt1, *stmt2;
    Single_Group_Join(Stmt *s1, Stmt *s2) { stmt1 = s1; stmt2 = s2; }
    ~Single_Group_Join() {
        delete stmt1; stmt1 = Stmt::Null;
        delete stmt2; stmt2 = Stmt::Null;
    }
	void gen() {
		stmt1->gen();   // Single_Group->gen()
		stmt2->gen();   // Single_Group_Join->gen();s
	}
};

#endif