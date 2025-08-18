#pragma once
#include "expr.h"
#include "token.h"

class Ternary : public Expr {
    public:
        Expr* left;
        Expr* middle;
        Expr* right;

        Ternary(Expr* left, Expr* middle, Expr* right) : left(left), middle(middle), right(right) {}
        Object accept(Oprt* oprt) override {
            return oprt->oprtTernary(this);
        }
};

class Binary : public Expr {
    public:
        Expr* left;
        Token* operatorr;
        Expr* right;

        Binary(Expr* left, Token* operatorr, Expr* right) : left(left), operatorr(operatorr), right(right) {}
        Object accept(Oprt* oprt) override {
            return oprt->oprtBinary(this);
        }
};

class Grouping : public Expr {
    public:
        Expr* expression;

        Grouping(Expr* expression) : expression(expression) {}
        Object accept(Oprt* oprt) override {
            return oprt->oprtGrouping(this);
        }
};

class Literal : public Expr {
    public:
        Object* value;

        Literal(Object* value) : value(value) {}
        Object accept(Oprt* oprt) override {
            return oprt->oprtLiteral(this);
        }
};

class Unary : public Expr {
    public:
        Token* operatorr;
        Expr* right;

        Unary(Token* operatorr, Expr* right) : operatorr(operatorr), right(right) {}
        Object accept(Oprt* oprt) override {
            return oprt->oprtUnary(this);
        }
};

