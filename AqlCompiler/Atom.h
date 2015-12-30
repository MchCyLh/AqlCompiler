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
	void gen(){
		if (s != Stmt::Null){//multiple token
			s->gen();//column gen update __column
			vector<Record_Cell> temp(ntr[__from_list[__column.first]][__column.second]);//the copy of the selected col_data
			vector<Record_Cell> stemp(temp);
			for (int i = 0; i < temp.size(); i++){
				stemp[i].content = "(?:";//all the stemp is (?:
				temp[i].content += ")";//all the temp is xxx)
				stemp[i].content += temp[i].content;//(?:xxx)
			}
			pattern_spec.push_back(stemp);
		}
		else{//single regex
			Word* r = static_cast<Word*>(reg);
			vector<Record_Cell> temp;
			string update_reg = "(?:";
			for (int i = 0; i < r->lexeme.size(); i++){
				if (i == 0 && r->lexeme[i] == '('){
					update_reg.push_back('(');
					update_reg.push_back('?');
					update_reg.push_back(':');
				}
				else if (i>0 && r->lexeme[i] == '('){
					if (r->lexeme[i - 1] != '\\'){
						update_reg.push_back('(');
						update_reg.push_back('?');
						update_reg.push_back(':');
					}
					else{
						update_reg.push_back(r->lexeme[i]);
					}
				}
				else{
					update_reg.push_back(r->lexeme[i]);
				}
			}
			update_reg += ")";
			Record_Cell rc(update_reg, 0, 0);
			temp.push_back(rc);
			pattern_spec.push_back(temp);
		}
	}
};

