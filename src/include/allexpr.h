#pragma once
#include "expr.h"
#include "token.h"

template <typename T>
class Binary : public Expr<T> {
    public:
        Expr<T>* left;
        Token* operatorr;
        Expr<T>* right;

        Binary(Expr<T>* left, Token* operatorr, Expr<T>* right) : left(left), operatorr(operatorr), right(right) {}
        T accept(Oprt<T>* oprt) override {
            return oprt->oprtBinary(this);
        }
};

template <typename T>
class Grouping : public Expr<T> {
    public:
        Expr<T>* expression;

        Grouping(Expr<T>* expression) : expression(expression) {}
        T accept(Oprt<T>* oprt) override {
            return oprt->oprtGrouping(this);
        }
};

template <typename T>
class Literal : public Expr<T> {
    public:
        Object* value;

        Literal(Object* value) : value(value) {}
        T accept(Oprt<T>* oprt) override {
            return oprt->oprtLiteral(this);
        }
};

template <typename T>
class Unary : public Expr<T> {
    public:
        Token* operatorr;
        Expr<T>* right;

        Unary(Token* operatorr, Expr<T>* right) : operatorr(operatorr), right(right) {}
        T accept(Oprt<T>* oprt) override {
            return oprt->oprtUnary(this);
        }
};

