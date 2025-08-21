#pragma once
#include "stmt.h"
#include "token.h"
#include "oprtstmt.h"

class Expression : public Stmt {
    public:
        Expr* expression;

        Expression(Expr* expression) : expression(expression) {}
        Object accept(OprtStmt* oprt) override {
            return oprt->oprtExpression(this);
        }
};

class Print : public Stmt {
    public:
        Expr* expression;

        Print(Expr* expression) : expression(expression) {}
        Object accept(OprtStmt* oprt) override {
            return oprt->oprtPrint(this);
        }
};

class Var : public Stmt {
    public:
        Token* name;
        Expr* initializer;

        Var(Token* name, Expr* initializer) : name(name), initializer(initializer) {}
        Object accept(OprtStmt* oprt) override {
            return oprt->oprtVar(this);
        }
};

class Block : public Stmt {
    public:
        vector<Stmt*> statements;

        Block(vector<Stmt*> statements) : statements(statements) {}
        Object accept(OprtStmt* oprt) override {
            return oprt->oprtBlock(this);
        }
};

