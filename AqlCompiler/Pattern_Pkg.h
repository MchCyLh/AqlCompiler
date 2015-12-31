#ifndef PATTERN_PKG
#define PATTERN_PKG

#include "Stmt.h"
class Pattern_Pkg :
    public Stmt
{
public:
    Stmt *stmt1, *stmt2, *stmt3;
    Token *num1, *num2;
    Pattern_Pkg() {}
    ~Pattern_Pkg() {
        delete stmt1; stmt1 = Stmt::Null;
        delete stmt2; stmt2 = Stmt::Null;
        delete stmt3; stmt3 = Stmt::Null;
        delete num1; num1 = Token::Null;
        delete num2; num2 = Token::Null;
    }
    void init(Stmt *s1, Stmt *s2, Token *t1, Token *t2, Stmt *s3) {
        stmt1 = s1;
        stmt2 = s2;
        stmt3 = s3;
        num1 = t1;
        num2 = t2;
    }
	void gen(){
		if (stmt1 != Stmt::Null){ //single atom gen
			stmt1->gen();
		}
		else if (stmt2 != Stmt::Null){//multiple atom gen
			stmt2->gen();
			Num* t1 = static_cast<Num *>(num1);
			Num* t2 = static_cast<Num *>(num2);
			for (int i = 0; i < pattern_spec[pattern_spec.size() - 1].size(); i++){
				string reg = pattern_spec[pattern_spec.size() - 1][i].content;
				if (t1->value == 0){//{0,x},so that reg*
					reg += "?";
					string temp = reg;
					for (int i = 1; i < t2->value; i++){
						reg += temp; //reg*reg*...
					}
				}
				else{//{x,y},ps,x>0
					string temp1 = reg; // use for min
					string temp2 = reg + "?"; // use for max
					int min = t1->value;
					int max = t2->value;
					for (int i = 1; i < min; i++){
						reg += temp1;
					}
					for (int i = min; i < max; i++){
						reg += temp2;
					}
				}
				pattern_spec[pattern_spec.size() - 1][i].content = reg;
			}
		}
		else if (stmt3 != Stmt::Null){//pattern group gen
			stmt3->gen();
		}
		else{//multiple token
			Num* t1 = static_cast<Num *>(num1);
			Num* t2 = static_cast<Num *>(num2);
			Record_Cell numof("", t1->value, t2->value);
			vector<Record_Cell> r;
			r.push_back(numof);
			pattern_spec.push_back(r);
		}
	}
};

#endif