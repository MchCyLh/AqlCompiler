#ifndef ATOM_H
#define ATOM_H

#include "Stmt.h"
#include "Token.h"

class Atom :
    public Stmt
{
public:
    Stmt *s; Token *reg;
    Atom() {}
    ~Atom() {
        delete s; s = Stmt::Null;
        delete reg; reg = Token::Null;
    }
	static Atom *Null;
    void init(Stmt *s_, Token *t) { s = s_; reg = t; }
	void gen(){
		if (s != Stmt::Null){//multiple token
			s->gen();//column gen update __column
			vector<Record_Cell> temp(ntr[__from_list[__column.first]][__column.second]);//the copy of the selected col_data
			//vector<Record_Cell> stemp(temp);
			//for (int i = 0; i < temp.size(); i++){
			//	stemp[i].content = "(?:";//all the stemp is (?:
			//	temp[i].content += ")";//all the temp is xxx)
			//	stemp[i].content += temp[i].content;//(?:xxx)
			//}
			//pattern_spec.push_back(stemp);
			pattern_spec.push_back(temp);
			__isgroup[pattern_spec.size() - 1]=group_num;
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
			vector<vector<int> > result;
			result = findall(update_reg.c_str(), text);
			for (int i = 0; i < result.size(); i++){
				/*string temp;
				for (int j = result[i][0]; j < result[i][1]; j++){
				temp.push_back(*(text + j));
				}*/
				int group_count = 0;
				for (int j = 0; j < result[0].size(); j += 2, group_count++){
					//printf("(%d,%d)", result[i][j], result[i][j + 1]);
					string tempstr;
					for (int k = result[i][j]; k < result[i][j + 1]; k++){
						tempstr.push_back(*(text + k));
					}
					Record_Cell r(tempstr, result[i][j], result[i][j + 1]);
					temp.push_back(r);
				}
				/*cout << temp;
				printf(":");
				printf("\n");*/
			}
			pattern_spec.push_back(temp);
			__isgroup[pattern_spec.size() - 1] = group_num;
		}
	}
};

#endif