#ifndef PATTERN_GROUP_H
#define PATTERN_GROUP_H

#include "Stmt.h"
class Pattern_Group :
    public Stmt
{
public:
    Stmt *s;
    Pattern_Group() {}
    ~Pattern_Group() {
        delete s; s = Stmt::Null;
    }
    void init(Stmt * s_) { s = s_; }
	void gen(){
		/*vector<Record_Cell> lbrach;
		Record_Cell l("(", 0, 0);
		lbrach.push_back(l);
		pattern_spec.push_back(lbrach);*/
		group_num++;
		s->gen();
		group_num--;
		/*vector<Record_Cell> rbrach;
		Record_Cell r(")", 0, 0);
		rbrach.push_back(r);
		pattern_spec.push_back(rbrach);*/
		/*for (int i = 0; i < pattern_spec[pattern_spec.size() - 1].size(); i++){
			string reg = "(";
			reg += pattern_spec[pattern_spec.size() - 1][i].content+")";
			pattern_spec[pattern_spec.size() - 1][i].content = reg;
		}*/
	}
};

#endif