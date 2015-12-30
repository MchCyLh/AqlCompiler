#include "TypeDefine.h"

Name_Table_Relation ntr;

map< string, string > __from_list;
vector< vector<string> > __select_list;
pair<string, string> __column;
Table __target_table;
map<int, string> __groups;

string __alias;

const string NoNeed = "";


void globalInit() {
    __from_list.clear();
    __select_list.clear();
    __target_table.clear();
    __groups.clear();
    __alias = "";
}