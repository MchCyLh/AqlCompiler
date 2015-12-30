#pragma once
#include "Stmt.h"
#include "regex.h"
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
		dfs(0, "");
		pattern_spec.clear();
	}
	void dfs(int deep, string re){
		if (deep == pattern_spec.size()){
			const char* regex = re.c_str();
			vector<vector<int> > result;
			result = findall(regex, text);
			for (int i = 0; i < result.size(); i++){
				/*string temp;
				for (int j = result[i][0]; j < result[i][1]; j++){
					temp.push_back(*(text + j));
				}*/
				int group_count = 0;
				for (int j = 0; j < result[0].size(); j += 2,group_count++){
					//printf("(%d,%d)", result[i][j], result[i][j + 1]);
					string temp;
					for (int k = result[i][j]; k < result[i][j + 1]; k++){
						temp.push_back(*(text + k));
					}
					Record_Cell r(temp, result[i][j], result[i][j + 1]);
					__target_table[__groups[group_count]].push_back(r);
				}
				/*cout << temp;
				printf(":");
				printf("\n");*/
			}
			return;
		}
		else{
			for (int i = 0; i < pattern_spec[deep].size(); i++){
				dfs(deep + 1, re + pattern_spec[deep][i].content+"[ ]?");
			}
		}
	}
};

