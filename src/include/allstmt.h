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

class If : public Stmt {
    public:
        Expr* condition;
        Stmt* thenBranch;
        std::vector<std::pair<Expr*,Stmt*>> elifBranches;
        Stmt* elseBranch;

        If(Expr* condition, Stmt* thenBranch, std::vector<std::pair<Expr*,Stmt*>> elifBranches, Stmt* elseBranch) : condition(condition), thenBranch(thenBranch), elifBranches(elifBranches), elseBranch(elseBranch) {}
        Object accept(OprtStmt* oprt) override {
            return oprt->oprtIf(this);
        }
};

class While : public Stmt {
    public:
        Expr* condition;
        Stmt* body;

        While(Expr* condition, Stmt* body) : condition(condition), body(body) {}
        Object accept(OprtStmt* oprt) override {
            return oprt->oprtWhile(this);
        }
};

class Function : public Stmt {
    public:
        Token* name;
        vector<Token*> parameters;
        Stmt* body;

        Function(Token* name, vector<Token*> parameters, Stmt* body) : name(name), parameters(parameters), body(body) {}
        Object accept(OprtStmt* oprt) override {
            return oprt->oprtFunction(this);
        }
};

class Wcall : public Stmt {
    public:
        Expr* callExpr;

        Wcall(Expr* callExpr) : callExpr(callExpr) {}
        Object accept(OprtStmt* oprt) override {
            return oprt->oprtWcall(this);
        }
};

class Return : public Stmt {
    public:
        Token* keyword;
        Expr* value;

        Return(Token* keyword, Expr* value) : keyword(keyword), value(value) {}
        Object accept(OprtStmt* oprt) override {
            return oprt->oprtReturn(this);
        }
};

