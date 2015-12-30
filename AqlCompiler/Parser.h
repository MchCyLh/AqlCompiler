#ifndef PARSER_H
#define PARSER_H
#include <iostream>
using namespace std;

#include "Tag.h"
#include "Lexer.h"
#include "Stmt.h"
#include "Seq.h"
#include "Create_Stmt.h"
#include "Select_Stmt.h"
#include "Select_Item_Join.h"
#include "Select_Item.h"
#include "Alias.h"
#include "From_Item_Join.h"
#include "From_Item.h"
#include "Extract_Stmt.h"
#include "Regex_Spec.h"
#include "Column.h"
#include "Name_Spec.h"
#include "Single_Group.h"
#include "Single_Group_Join.h"
#include "Pattern_Spec.h"
#include "Pattern_Pkg_Join.h"
#include "Pattern_Pkg.h"
#include "Atom.h"
#include "Pattern_Group.h"

#include "Output_Stmt.h"

class Parser
{
private:
    Lexer *lex; // 词法分析器
    Token *look;    // 下一个Token
public:
    //void setLook(Token *t) { delete look; look = t; }   // 设置look，删除原来的对象，防止内存泄露
    Parser(Lexer *l) { lex = l; move(); }
    void move() { look = lex->scan(); } // 移动到下一个Token
    void match(int t) { // 匹配Token类型是否为t
        if (look->tag == t) move();
        else {
            cout << "Syntax error" << endl;
            // #.抛出异常,输出异常信息到控制台，并且停止整个程序的运行.
            // exit(1);
        }
    }

    void program() {
        Stmt *s = aql_stmts();
        // #.对语法树进行处理
        s->gen();   // Seq-gen();
    }

    Stmt * aql_stmts() {    // aql_stmts ->aql_stmt aql_stmts | e
        if (look->tag == Tag::END) return Stmt::Null;
        else {
            Stmt *s1 = aql_stmt();
            Stmt *s2 = aql_stmts();
            return new Seq(s1, s2);
        }
    }

    Stmt * aql_stmt() { // aql_stmt -> create_stmt ; | output_stmt ;
        Stmt * s;
        switch (look->tag) {
        case Tag::CREATE:
        s = create_stmt(); match(';');
        return s;
        case Tag::OUTPUT:
        s = output_stmt(); match(';');
        return s;
        default:
        // #.输出错误信息终止程序
        return Stmt::Null;
        }
    }

    Stmt * create_stmt() {  // create_stmt -> create view ID as view_stmt
        Create_Stmt * cs = new Create_Stmt();
        match(Tag::CREATE); match(Tag::VIEW);
        Token *t = look;
        match(Tag::ID); match(Tag::AS);
        Stmt * s = view_stmt();
        cs->init(t, s);
        return cs;
    }

    Stmt *view_stmt() { // view_stmt -> select_stmt | extract_stmt
        // Word * word = (Word *)look;
        if (look->tag == Tag::SELECT) return select_stmt();
        else return extract_stmt();
    }

    Stmt *select_stmt() {   // select_stmt -> select select_list from from_list
        Select_Stmt * ss = new Select_Stmt();
        match(Tag::SELECT);
        Stmt *s1 = select_list();
        match(Tag::FROM);
        Stmt *s2 = from_list();
        ss->init(s1, s2);
        return ss;
    }

    Stmt *select_list() {   // select_list -> select_item | select_list select_item
        Stmt * s = select_item();
        while (look->tag == ',') {  // Token# : ',' Token 中的tag赋值为','
            move();     // !!!可能存在内存泄露问题 可改为 match(',');
            s = new Select_Item_Join(s, select_item());
        }
        return s;
    }

    Stmt *select_item() {   // select_item -> ID . ID alias
        Select_Item *si = new Select_Item();
        Token *t1 = look;   move();   match('.');
        Token *t2 = look;   match(Tag::ID);
        Stmt *s = alias();
        si->init(t1, t2, s);
        return si;
    }

    Stmt *alias() { // alias -> as ID | e
        Alias *a = new Alias();
        if (look->tag == Tag::AS) {
            move();
            Token *t = look;
            match(Tag::ID);
            a->init(t);
            return a;
        } else {
            return Alias::Null;
        }
    }

    Stmt * from_list() { // from_list -> from_item | from_list , from_item
        Stmt *s = from_item();
        while (look->tag == ',') {
            move();
            s = new From_Item_Join(s, from_item());
        }
        return s;
    }

    Stmt * from_item() {    // from_item -> ID ID
        From_Item *fi = new From_Item();
        Token *t1 = look;
        move();
        Token *t2 = look;
        match(Tag::ID);
        fi->init(t1, t2);
        return fi;
    }

    // extract_stmt begin
    Stmt *extract_stmt() {  // extract_stmt ->  extract extract_spec from from_list
        Extract_Stmt *es = new Extract_Stmt();
        match(Tag::EXTRACT);
        Stmt *s1 = extract_spec();
        match(Tag::FROM);
        Stmt *s2 = from_list();
        es->init(s1, s2);
        return es;
    }

    Stmt *extract_spec() {  // extract_spec -> regex_spec | pattern_spec
        if (look->tag == Tag::REGEX) return regex_spec();
        else return pattern_spec();
    }

    Stmt *regex_spec() {    // regex_spec -> regex REG on column name_spec
        Regex_Spec *rs = new Regex_Spec();
        match(Tag::REGEX);
        Token *t = look;
        match(Tag::ON);
        Stmt *s1 = column();
        Stmt *s2 = name_spec();
        rs->init(t, s1, s2);
        return rs;
    }

    Stmt *column() {    // column -> ID . ID
        Column *c = new Column();
        Token *t1 = look; match(Tag::ID); match('.');
        Token *t2 = look; match(Tag::ID);
        c->init(t1, t2);
        return c;
    }

    Stmt *name_spec() { // name_spec -> as ID | return group_spec
        Name_Spec *ns = new Name_Spec();
        if (look->tag == Tag::AS) {
            move(); Token *t = look; match(Tag::ID);
            ns->init(t);
        } else {
            match(Tag::RETURN);
            Stmt *s = group_spec();
            ns->init(s);
        }
        return ns;
    }

    Stmt *group_spec() {    // group_spec → single_group | group_spec and single_group
        Stmt * s = single_group();
        while (look->tag == Tag::AND) {
            move(); s = new Single_Group_Join(s, single_group());
        }
        return s;
    }

    Stmt *single_group() {  // single_group → group NUM as ID
        Single_Group *sg = new Single_Group();
        match(Tag::GROUP); Token *t1 = look; match(Tag::NUM);
        match(Tag::AS); Token *t2 = look; match(Tag::ID);
        sg->init(t1, t2);
        return sg;
    }

    Stmt * pattern_spec() { // pattern_spec → pattern pattern_expr name_spec
        Pattern_Spec *ps = new Pattern_Spec();
        match(Tag::PATTERN);
        Stmt *s1 = pattern_expr();
        Stmt *s2 = name_spec();
        ps->init(s1, s2);
        return ps;
    }
    
    Stmt *pattern_expr() {  // pattern_expr → pattern_pkg | pattern_expr pattern_pkg
        Stmt *s = pattern_pkg();
        while (look->tag == '(' || look->tag == '<' || look->tag == Tag::REGEX) {
            s = new Pattern_Pkg_Join(s, pattern_pkg());
        }
        return s;
    }

    Stmt *pattern_pkg() {   // pattern_pkg → atom | atom { NUM , NUM } | pattern_group
        Pattern_Pkg * pp = new Pattern_Pkg();
        
        Stmt *s1 = Stmt::Null, *s2 = Stmt::Null, *s3 = Stmt::Null;
        Token *t1 = Token::Null, *t2 = Token::Null;
        if (look->tag == '(') {
            s3 = pattern_group();
        } else {
            s1 = atom();
            if (look->tag == '{') {
                s2 = s1; s1 = Stmt::Null;
                move(); t1 = look; match(Tag::NUM);
                match(','); t2 = look; match(Tag::NUM); match('}');
            }
        }

        pp->init(s1, s2, t1, t2, s3);
        return pp;
    }

    Stmt *atom() {  // atom→ < column > | < Token > | REG
        Atom *a = new Atom();
        Stmt *s = Stmt::Null; Token *t=Token::Null;
        
        if (look->tag == Tag::REGEX) {
            match(Tag::REGEX);
            t = look;
        } else {
            match('<');
            if (look->tag == Tag::TOKEN) {
                move();
            } else {
                s = column();
            }
            match('>');
        }
        a->init(s, t);
        return a;
    }

    Stmt *pattern_group() { // pattern_group → ( pattern_expr )
        Pattern_Group *pg = new Pattern_Group();
        match('('); Stmt *s = pattern_expr(); match(')');
        pg->init(s);
        return pg;
    }

    // extract_stmt end
   
    Stmt * output_stmt() {
        Output_Stmt *os = new Output_Stmt();
        match(Tag::OUTPUT); match(Tag::VIEW);
        Token *t = look; match(Tag::ID);
        Stmt *s = alias();
        os->init(t, s);
        return os;
    }
};

#endif