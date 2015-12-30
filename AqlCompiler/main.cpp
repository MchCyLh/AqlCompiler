#include "Parser.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int main() {

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
