#pragma once
#include "token.h"

class Expression;
class Print;
class Var;
class Block;
class If;
class While;
class Function;
class Wrapper;
class Return;
class Class;

class OprtStmt {
    public:
        virtual Object oprtExpression(Expression* stmt) = 0;
        virtual Object oprtPrint(Print* stmt) = 0;
        virtual Object oprtVar(Var* stmt) = 0;
        virtual Object oprtBlock(Block* stmt) = 0;
        virtual Object oprtIf(If* stmt) = 0;
        virtual Object oprtWhile(While* stmt) = 0;
        virtual Object oprtFunction(Function* stmt) = 0;
        virtual Object oprtWrapper(Wrapper* stmt) = 0;
        virtual Object oprtReturn(Return* stmt) = 0;
        virtual Object oprtClass(Class* stmt) = 0;
        virtual ~OprtStmt() noexcept(false) = default;
};

