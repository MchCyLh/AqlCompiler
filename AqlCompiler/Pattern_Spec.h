#ifndef PATTERN_SPEC_H
#define PATTERN_SPEC_H

#include "Stmt.h"
#include "regex.h"
#include<cstring>
#include<iostream>
using namespace std;
class Pattern_Spec :
    public Stmt
{
public:
    Stmt *stmt1, *stmt2;
    Pattern_Spec() {}
    void init(Stmt *s1, Stmt *s2) { stmt1 = s1; stmt2 = s2; }
	void gen(){
		stmt2->gen();
		stmt1->gen();
		/*for (int i = 0; i < pattern_spec[0].size(); i++){
			dfs(1, pattern_spec[0][i].content+"[ ]*?", pattern_spec[0][i].begin, pattern_spec[0][i].end);
		}*/
		vector<Record_Cell> path;
		dfs(0, path, 0, 0);

		pattern_spec.clear();
		__groups.clear();
	}
	void dfs(int deep, vector<Record_Cell> path,int t1,int t2){
		if (deep == pattern_spec.size()){
			int g = 0;
			for (int i = 0; i < path.size(); i++){
				if (__isgroup[i]>0){
					__target_table[__groups[g + 1]].push_back(path[i]);
					g++;
				}
			}
			int s = path[0].begin;
			int e = path[path.size() - 1].end;
			string g0;
			for (int i = s; i < e; i++){
				g0.push_back(*(text + i));
			}
			Record_Cell r(g0, s, e);
			__target_table[__groups[0]].push_back(r);
			return;
		}
		else{
			if (pattern_spec[deep][0].content == ""){//<Token>{1,2}
				dfs(deep + 1, path, t1 + pattern_spec[deep][0].begin, t2 + pattern_spec[deep][0].end);
			}
			if (!path.empty()){//<x,x> <x,y> | <Token>{1,2} <x,y>
				for (int i = 0; i < pattern_spec[deep].size(); i++){
					Record_Cell r(pattern_spec[deep][i].content, pattern_spec[deep][i].begin,
						pattern_spec[deep][i].end);
					int token_num = get_token_num(path[path.size() - 1].end, r.begin);
					if (token_num>=t1 && token_num<=t2){
						path.push_back(r);
						dfs(deep + 1, path, 0, 0);
						path.pop_back();
					}
				}
			}
			else {//path empty
				for (int i = 0; i < pattern_spec[deep].size(); i++){
					Record_Cell r(pattern_spec[deep][i].content, pattern_spec[deep][i].begin, 
																 pattern_spec[deep][i].end);
					path.push_back(r);
					dfs(deep + 1,path,t1,t2);
					path.pop_back();
				}
			}
		}
	}

	int get_token_num(int x, int y){
        int t = tokenizer->get_token_num(x, y);
        return t;
	}

};

#endif