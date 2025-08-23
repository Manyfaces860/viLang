#pragma once
#include "token.h"

class Expression;
class Print;
class Var;
class Block;
class If;

class OprtStmt {
    public:
        virtual Object oprtExpression(Expression* stmt) = 0;
        virtual Object oprtPrint(Print* stmt) = 0;
        virtual Object oprtVar(Var* stmt) = 0;
        virtual Object oprtBlock(Block* stmt) = 0;
        virtual Object oprtIf(If* stmt) = 0;
        virtual ~OprtStmt() noexcept(false) = default;
};

