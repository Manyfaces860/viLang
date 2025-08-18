#pragma once
#include "expr.h"
#include "oprt.h"
#include "allexpr.h"
#include <string>

using std::string;


class AstPrinter : public Oprt {
    public:

        string prints(Expr* expr);
        
        Object oprtTernary(Ternary* expr) override;

        Object oprtBinary(Binary* expr) override;

        Object oprtGrouping(Grouping* expr) override;

        Object oprtLiteral(Literal* expr) override;

        Object oprtUnary(Unary* expr) override;

    private:
        string parenthesize(string name, Expr* expr);

        string parenthesize(string name, Expr* expr1, Expr* expr2);

        string parenthesize(Expr* expr1, Expr* expr2, Expr* expr3);

};
