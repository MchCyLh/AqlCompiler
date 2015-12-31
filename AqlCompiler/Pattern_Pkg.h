#ifndef PATTERN_PKG
#define PATTERN_PKG

#include "Stmt.h"
#include <set>
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
			vector<Record_Cell> temp;
			set<string> past;
			for (int i = 0; i < pattern_spec[pattern_spec.size() - 1].size(); i++){
				string reg = "(?:" + pattern_spec[pattern_spec.size() - 1][i].content + ")";
				if (past.count(reg)){ 
					continue; 
				}
				past.insert(reg);
				if (t1->value == 0){//{0,x},so that ""
					string temp1 = "";
					temp.push_back(Record_Cell(temp1, 0, 0));
					pattern_spec.pop_back();
					pattern_spec.push_back(temp);
					break;
				}
				else{//{x,y},ps,x>0
					string temp1 = reg + "[ ]*?"; // use for min
					string temp2 = reg + "?[ ]*?"; // use for max
					int min = t1->value;
					int max = t2->value;
					reg += "[ ]*?";
					for (int i = 1; i < min; i++){
						reg += temp1;
					}
					for (int i = min; i < max; i++){
						reg += temp2;
					}
					vector<vector<int> > result;
					result = findall(reg.c_str(), text);
					for (int i = 0; i < result.size(); i++){
						int group_count = 0;
						for (int j = 0; j < result[0].size(); j += 2, group_count++){
							string tempstr;
							for (int k = result[i][j]; k < result[i][j + 1]; k++){
								tempstr.push_back(*(text + k));
							}
							Record_Cell r(tempstr, result[i][j], result[i][j + 1]);
							temp.push_back(r);
						}
					}
				}
			}
			pattern_spec.pop_back();
			pattern_spec.push_back(temp);
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