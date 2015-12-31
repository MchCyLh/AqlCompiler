#ifndef RECORD_CELL_H
#define RECORD_CELL_H
#include <string>
using std::string;

class Record_Cell
{
public:
    string content;
    int begin;
    int end;
    Record_Cell() {}
    Record_Cell(const string &s, int b, int e) : content(s), begin(b), end(e) {}
};

#endif