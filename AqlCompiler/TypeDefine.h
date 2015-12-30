#pragma once

#include <map>
#include <string>
#include <vector>
using namespace std;

#include "Record_Cell.h"
#include "regex.h"

typedef map< string, vector<Record_Cell> > Table;
typedef map<string, string> Name_Mapping_Relation;
typedef map< string, Table > Name_Table_Relation;

extern map< string, string > __from_list;
extern vector< vector<string> > __select_list;
extern pair<string, string> __column;
extern Name_Table_Relation ntr;
extern Table __target_table;
extern map<int, string> __groups;

extern string __alias;

extern string NoNeed;