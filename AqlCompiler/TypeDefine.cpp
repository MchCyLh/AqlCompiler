#include "TypeDefine.h"

map< string, string > __from_list;
vector< vector<string> > __select_list;
pair<string, string> __column;
Name_Table_Relation ntr;
Table __target_table;

string __alias;
vector<vector<Record_Cell> > pattern_spec;
//char* text;

map<int, string> __groups;
const string NoNeed = "";

ofstream ofs;

void globalInit() {
	__from_list.clear();
	__select_list.clear();
	__target_table.clear();
	__groups.clear();
	__alias = "";
}