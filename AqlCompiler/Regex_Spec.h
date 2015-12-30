#pragma once
#include "Stmt.h"
#include "TypeDefine.h"

class Regex_Spec :
    public Stmt
{
public:
    Token *reg;
    Stmt *stmt1, *stmt2;
    Regex_Spec() {}
    void init(Token *t, Stmt *s1, Stmt *s2) { reg = t; stmt1 = s1; stmt2 = s2; }

    void gen() {
        Reg *regex = static_cast<Reg *>(reg);   // 正则
        const char *regex_text = regex->lexeme.c_str();
        stmt1->gen();   // Column->gen();
        stmt2->gen();   // Single_Group->gen() | Single_Group_Join->gen()
        // 生成target table
        string &table_name = __from_list[__column.first];
        Table &table = ntr[table_name];
        vector<Record_Cell> &cols = table[__column.second];
        for (int i = 0; i < cols.size(); ++i) {
            const char *text = cols[i].content.c_str();
            vector< vector<int> > &results = findall(regex_text, text);
            for (int j = 0; j < results.size(); ++j) {
                vector<int> &result = results[j];
                for (int k = 0; k < result.size(); k += 2) {
                    if (!(__groups[k/2] == NoNeed)) {
                        string &group_name = __groups[k];
                        vector<Record_Cell> &cur_cols = __target_table[group_name];
                        Record_Cell record_cell;
                        record_cell.content = cols[i].content.substr(result[k], result[k + 1]);
                        record_cell.begin = result[k];
                        record_cell.end = result[k + 1];
                        cur_cols.push_back(record_cell);
                    }
                }
            }
        }
    }
};

