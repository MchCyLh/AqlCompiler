#pragma once

#include "Stmt.h"
#include "TypeDefine.h"

class Seq : public Stmt
{
public:
    Stmt * stmt1, *stmt2;
    Seq(Stmt *s1, Stmt *s2) { stmt1 = s1, stmt2 = s2; }

		void gen() {
			if (stmt1 != Stmt::Null) stmt1->gen();
			globalInit();
			if (stmt2 != Stmt::Null) stmt2->gen();
		}
};

