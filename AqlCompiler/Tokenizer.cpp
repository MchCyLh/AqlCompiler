#include "Tokenizer.h"
#include<fstream>
using namespace std;

Tokenizer::Tokenizer(string file_path) {
	//file = file_path;
	fin.open(file_path);
	if (!fin) {
		cerr << "open " << file_path << " false" << endl;
		exit(1);
	}
	char ch;
	int new_token = 1;
	string token_string = "";
	//Token* goal_token = new Token();
	//Token temp_token;
	//int size = 0;
	int number = -1;
	while (fin.get(ch)) {
		number++;
		//left_num++;
		if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
			//string token_string = goal_token -> get_token();
			token_string += ch;
			//int token_last = goal_token -> get_stop_num();
			//right_num++;
			
			if (new_token == 0) {
				//goal_token->setToken(token_string, goal_token->get_start_num(), goal_token->get_stop_num() + 1);
			} else {
				//goal_token -> setToken(token_string, left_num, left_num);
				//right_num = left_num;
				left_num = number;
				new_token = 0;
			}
			
			if (fin.peek()) {
				ch = fin.peek();
				if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
				}
				else {
					//size++;
					new_token = 1;
					token_num.push_back(pair<int, int>(left_num, size));
					size++;
					//break;
				}
			}
		}
		else if (ch == 32 || ch == 13 || ch == 10 || ch == '\t') {
		}
		else {
			//string temp = "";
			token_string += ch;
			//goal_token -> setToken(temp, left_num, left_num);
			//size++;
			//right_num = left_num;
			//int type = token_string[0];
			left_num = number;
			token_num.push_back(pair<int, int>(left_num, size));
			size++;
			//break;
		}
	}
	if (!fin.peek()) {
		if (new_token == 0) {
			//size++;
			left_num = number;
			token_num.push_back(pair<int, int>(left_num, size));
		}
		/*
		else {
			//goal_token -> setToken("", 0, 0);
			int type = Tag::END;
		}
		*/
	}
	//Word* temp = new Word(token_string, 271);
	//temp->set_time(left_num, right_num);
	/*
	ifstream fin(file_path);
	if (!fin) {
		cerr << "open " << file_path << " false" << endl;
		exit(1);
	}
	char ch;
	int new_token = 1;
	Token temp_token;
	int loc = -1;
	while (fin.get(ch)) {
		loc ++;
		if ((ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) {
			string token_string = temp_token.get_token();
			token_string += ch;
			int token_last = temp_token.get_stop_num();
			if (new_token == 0) {
				temp_token.setToken(token_string, temp_token.get_start_num(), temp_token.get_stop_num() + 1);
			} else {
				temp_token.setToken(token_string, loc, loc);
				new_token = 0;
			}
		} else if (ch == 32 || ch == 13 || ch == 10) {
			if (new_token == 0) {
				new_token = 1;
				all_the_token.push_back(temp_token);
				size ++;
				temp_token.setToken("", 0, 0);
			}
		} else {
			if (new_token == 0) {
				new_token = 1;
				all_the_token.push_back(temp_token);
				size ++;
				string temp = "";
				temp += ch;
				temp_token.setToken(temp, loc, loc);
				all_the_token.push_back(temp_token);
				size ++;
				temp_token.setToken("", 0, 0);
			} else {
				string temp = "";
				temp += ch;
				temp_token.setToken(temp, loc, loc);
				all_the_token.push_back(temp_token);
				size ++;
				temp_token.setToken("", 0, 0);
			}
		}
	}
	if (new_token == 0) {
		all_the_token.push_back(temp_token);
		size++;
	}
	*/
}
/*
Token Tokenizer::next() {
	if (number < size) {
		number++;
		return all_the_token[number-1];
		
	} else {
		cerr << " what you want is out of the size" << endl;
		exit(1);
	}
}
*/
/*
Token* Tokenizer::scan(){
	char ch;
	int new_token = 1;
	string token_string = "";
	//Token* goal_token = new Token();
	//Token temp_token;
	while (fin.get(ch)) {
		left_num++;
		if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
			//string token_string = goal_token -> get_token();
			token_string += ch;
	       //int token_last = goal_token -> get_stop_num();
			right_num++;
			
			if (new_token == 0) {
				//goal_token->setToken(token_string, goal_token->get_start_num(), goal_token->get_stop_num() + 1);
			} else {
				//goal_token -> setToken(token_string, left_num, left_num);
				right_num = left_num;
				new_token = 0;
			}
			
			if (fin.peek()) {
				ch = fin.peek();
				if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
				} else {
					//size++;
					new_token = 1;
					break;
				}
			}
		}
		else if (ch == 32 || ch == 13 || ch == 10 || ch == '\t') {
		} else {
			//string temp = "";
			token_string += ch;
			//goal_token -> setToken(temp, left_num, left_num);
			//size++;
			right_num = left_num;
			int type = token_string[0];
			break;
		}
	}
	if (!fin.peek()) {
		if (new_token == 0) {
			//size++;
		} else {
			//goal_token -> setToken("", 0, 0);
			int type = Tag::END;
		}
	}
	Word* temp = new Word(token_string, 271);
	temp->set_time(left_num, right_num);
	return temp;
}
*/
/*
int Tokenizer::get_size() {
	return size;
}
*/
vector<pair<int, int>> & Tokenizer::get_vector() {
	return token_num;
}

Tokenizer::~Tokenizer() {
	fin.close();
}

int Tokenizer::get_token_num(int left, int right) {
    // token_num;
    // 取left的上限token postion
    int l = -1, r = token_num.size() - 1;
    while (l + 1 != r) {
        int mid = l + (r - l) / 2;
        pair<int, int> &p = token_num[mid];
        if (left <= p.first) {
            r = mid;
        } else {
            l = mid;
        }
    }
    int left_token_num = token_num[r].second;

    // 取right的下线token position
    l = 0; r = token_num.size();
    while (l + 1 != r) {
        int mid = l + (r - l) / 2;
        pair<int, int> &p = token_num[mid];
        if (right < p.first) {
            r = mid;
        } else {
            l = mid;
        }
    }
    int right_token_num = token_num[l].second;

    return right_token_num - left_token_num;
}