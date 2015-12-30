#include "Parser.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    /*Table table1;
    vector<Record_Cell> cols1;
    cols1.push_back(Record_Cell("Jane", 0, 4));
    cols1.push_back(Record_Cell("Stephan", 4, 5));
    cols1.push_back(Record_Cell("Demo", 5, 6));
    cols1.push_back(Record_Cell("Elena", 6 ,7));
    table1["name"] = cols1;
    ntr["Actor"] = table1;*/

    // Éú³ÉDocument
    Table &table = ntr["Document"];
    vector<Record_Cell> &cols = table["text"];
    Record_Cell record_cell;
    const char * document = "document.input";
    ifstream ifs(document);
    stringstream buffer;
    buffer << ifs.rdbuf();
    record_cell.content = buffer.str();
    record_cell.begin = 0;
    record_cell.end = record_cell.content.size();
    cols.push_back(record_cell);

    
    string aql_name = "test.aql";
    Lexer *lexer = new Lexer(aql_name);
    Parser parser(lexer);
    parser.program();

    return 0;
}