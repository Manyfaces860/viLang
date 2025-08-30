#pragma once
#include "token.h"

class Ternary;
class Binary;
class Grouping;
class Literal;
class Unary;
class Variable;
class Assign;
class Logical;
class Call;

class Oprt {
    public:
        virtual Object oprtTernary(Ternary* expr) = 0;
        virtual Object oprtBinary(Binary* expr) = 0;
        virtual Object oprtGrouping(Grouping* expr) = 0;
        virtual Object oprtLiteral(Literal* expr) = 0;
        virtual Object oprtUnary(Unary* expr) = 0;
        virtual Object oprtVariable(Variable* expr) = 0;
        virtual Object oprtAssign(Assign* expr) = 0;
        virtual Object oprtLogical(Logical* expr) = 0;
        virtual Object oprtCall(Call* expr) = 0;
        virtual ~Oprt() noexcept(false) = default;
};

