#pragma once
#include "Stmt.h"
#include "TypeDefine.h"
#include <string>
using namespace std;

class Select_Stmt : public Stmt
{
public:
    Stmt * stmt1, *stmt2;
    Select_Stmt() {}
    void init(Stmt * s1, Stmt *s2) { stmt1 = s1; stmt2 = s2; }

    void gen() {
        stmt2->gen();   // From_Item->gen() | From_Item_Join->gen();
        stmt1->gen();   // Select_Item->gen() | Select_Item_Join->gen()
        // __from_list ºÍ __select_list
        // map<string, string> __from_list;
        // vector< vector<string> > __select_list;
        dfs(0, 1);
    }

    int dfs(int cur, int pre_times) {
        if (cur >= __select_list.size()) return 1;
        vector<string> &item = __select_list[cur];
		Table &table = ntr[__from_list[item[0]]];
		vector<Record_Cell> &cols = table[item[1]];// È¡ÁÐ
        string &alias_name = item[2];
        int count = dfs(cur+1, pre_times * cols.size());
        for (int k = 0; k < pre_times; ++k) {
            for (int i = 0; i < cols.size(); ++i) {
                vector<Record_Cell> & target_cols = __target_table[alias_name];
                for (int j = 0; j < count; ++j)
                    target_cols.push_back(cols[i]);
            }
        }
        return count * cols.size();
    }

};

