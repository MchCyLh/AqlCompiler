#pragma once
#include "Stmt.h"
class Pattern_Group :
    public Stmt
{
public:
    Stmt *s;
    Pattern_Group() {}
    void init(Stmt * s_) { s = s_; }
	void gen(){
		vector<Record_Cell> lbrach;
		Record_Cell l("(", 0, 0);
		lbrach.push_back(l);
		pattern_spec.push_back(lbrach);
		s->gen();
		vector<Record_Cell> rbrach;
		Record_Cell r(")", 0, 0);
		rbrach.push_back(r);
		pattern_spec.push_back(rbrach);
	}
};

