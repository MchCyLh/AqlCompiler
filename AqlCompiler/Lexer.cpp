#include "lexer.h";
#include <fstream>
#include <string>
using namespace std;


Lexer::Lexer(string file_path) {
	fin.open(file_path);
	if (!fin) {
		cerr << "open " << file_path << " false" << endl;
		exit(1);
	}
}

Token* Lexer::scan() {
	char ch;
	string token_string = "";
	int token_type = 0;
	while (fin.get(ch)) {
		col++;
		if (is_regex == 0) {
			if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
				token_string += ch;
				if (fin.peek()) {
					ch = fin.peek();
					if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
					}
					else {
						token_type = choose_type(token_string);
						break;
					}
				}
			} else if (ch == 32 || ch == 13 || ch == 10 || ch == '\t') {
				if (ch == 10) {
					row++;
					col = 0;
				}
			} else if (ch == 47){
				is_regex = 1;
			} else {
				token_string += ch;
				token_type = choose_type(token_string);
				break;
			}
		} else {
			if (ch == 47 && (fin.peek() == 10 || fin.peek() == 13 || fin.peek() == 32 || fin.peek() == '\t')) {
				is_regex = 0;
				token_type = Tag::REG;
				break;
			} else {
				token_string += ch;
			}
		}
	}
	if (token_string == "") {
		Token* end_token = new Token(Tag::END);
		return end_token;
	}
	if (token_type == Tag::NUM) {
		int number = 0;
		for (int i = 0; i < token_string.length(); i++) {
			 number += (token_string[i] - '0')*pow(10, (token_string.length() - i - 1));
		}
		Num* num_token = new Num(number);
		num_token->setType(Tag::NUM);
		num_token->set_time(row, col);
		return num_token;
	} else {
		Word* word_token = new Word(token_string, token_type);
		word_token->set_time(row, col);
		return word_token;
	}
}

int choose_type(string temp) {
	if (temp == "create") { return Tag::CREATE; }
	else if (temp == "view") { return Tag::VIEW; }
	else if (temp == "as") { return Tag::AS; }
	else if (temp == "output") { return Tag::OUTPUT; }
	else if (temp == "select") { return Tag::SELECT; }
	else if (temp == "from") { return Tag::FROM; }
	else if (temp == "extract") { return Tag::EXTRACT; }
	else if (temp == "regex") { return Tag::REGEX; }
	else if (temp == "on") { return Tag::ON; }
	else if (temp == "return") { return Tag::RETURN; }
	else if (temp == "group") { return Tag::GROUP; }
	else if (temp == "and") { return Tag::AND; }
	else if (temp == "Token") { return Tag::TOKEN; }
	else if (temp == "pattern") { return Tag::PATTERN; }
	else if (temp == "(") { return temp[0] - 0; }
	else if (temp == ")") { return temp[0] - 0; }
	else if (temp == "<") { return temp[0] - 0; }
	else if (temp == ">") { return temp[0] - 0; }
	else if (temp == ".") { return temp[0] - 0; }
	else if (temp == ";") { return temp[0] - 0; }
	else {
		bool num = 1;
		int number = 0;
		for (int i = 0; i < temp.length(); i++) {
			if (temp[i] < 48 || temp[i] > 57) {
				num = 0;
				break;
			}
		}
		if (num) {
			return Tag::NUM;
		}
		else {
			return Tag::ID;
		}
	}
}
