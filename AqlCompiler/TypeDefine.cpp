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
map<int, int> __isgroup;
int group_num = 0;

map<int, pair<int, int> >__pattern_group;
vector<pair<char, int> > __pattern_group_vector;
ofstream ofs;
Tokenizer *tokenizer;

void globalInit() {
	__from_list.clear();
	__select_list.clear();
	__target_table.clear();
	__groups.clear();
	__alias = "";
	__pattern_group_vector.clear();
	__pattern_group.clear();
	pattern_spec.clear();
}