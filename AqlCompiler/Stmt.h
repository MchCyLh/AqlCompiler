#ifndef STMT_H
#define STMT_H

#include "Node.h"
#include "TypeDefine.h"
#include "Token.h"
#include "Word.h"
#include "Num.h"
#include<string>

class Stmt : public Node
{
public:
    Stmt() {}
    static Stmt * Null; // ±Ì æø’”Ôæ‰
    virtual void gen() {}
    virtual void Delete() {}

    // virtual ~Stmt() {}
};

#endif