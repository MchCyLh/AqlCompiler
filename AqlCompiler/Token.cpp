#include "Token.h"
using namespace std;

Token * Token::Null = NULL;

Token::Token() {
	token = "";
	start = 0;
	stop = 0;
}
 Token::Token(string temp1, int temp2, int temp3) {
	 token = temp1;
	 start = temp2;
	 stop = temp3;
 }
 void Token::setToken(string temp1, int temp2, int temp3) {
	 token = temp1;
	 start = temp2;
	 stop = temp3;
 }

 void Token::setToken(string temp1) {
	 token = temp1;
 }

 void Token::setType(int ty) {
	 tag = ty;
 }

 void Token::set_time(int a, int b) {
	 start = a;
	 stop = b;
 }


 string Token::get_token() {
	 return token;
 }
 int Token::get_start_num() {
	 return start;
 }
 int Token::get_stop_num() {
	 return stop;
 }
 int Token::get_type() {
	 return tag;
 }
