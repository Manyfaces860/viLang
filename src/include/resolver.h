#pragma once
#include <string>
#include <vector>
#include "expr.h"
#include "token.h"
#include "allexpr.h"
#include "oprtstmt.h"
#include "stmt.h"


using std::string, std::vector;

class Interpreter;

class Resolver : public Oprt, public OprtStmt {

    vector<Stmt*> program;
    
    public:
    
        Resolver();
        Resolver(Interpreter* runtime);

        void resolve();

        void execute(Stmt* stmt);

        void runInteractive(Stmt* stmt);

        Object oprtTernary(Ternary* expr) override;

        Object oprtBinary(Binary* expr) override;

        Object oprtGrouping(Grouping* expr) override;

        Object oprtLiteral(Literal* expr) override;

        Object oprtUnary(Unary* expr) override;

        Object oprtPrint(Print* stmt) override;

        Object oprtExpression(Expression* stmt) override;

        Object oprtAssign(Assign* stmt) override;

        Object oprtVariable(Variable* expr) override;

        Object oprtVar(Var* expr) override;

        Object oprtBlock(Block* stmt) override;

        Object oprtIf(If* stmt) override;

        Object oprtLogical(Logical* expr) override;

        Object oprtWhile(While* stmt) override;

        Object oprtWcall(Wcall* stmt) override;

        Object oprtCall(Call* stmt) override;

        Object oprtFunction(Function* stmt) override;

        Object oprtReturn(Return* stmt) override;

        Object getGlobal(Token* token);

        // void setClock();

        // Object evaluate(Expr* expr);
        // bool isTruthy(const Object& obj);
        // bool isEqual(Object& left, Object& right);
        // void checkNumberOperands(Token& operatorr, Object& left, Object& right);
        // void checkNumberOperands(Token& operatorr, Object& right);

};
