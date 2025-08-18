#include <string>
#include "include/expr.h"
#include "include/oprt.h"
#include "include/allexpr.h"
#include "include/astprinter.h"
#include "include/util.h"

using std::string;

string AstPrinter::prints(Expr* expr) {
    return objectToString(expr->accept(this));
}

Object AstPrinter::oprtTernary(Ternary* expr) {
    return parenthesize(expr->left, expr->middle, expr->right);
}

Object AstPrinter::oprtBinary(Binary* expr) {
    return parenthesize(expr->operatorr->lexeme,
                expr->left, expr->right);
}

Object AstPrinter::oprtGrouping(Grouping* expr) {
    return parenthesize("group", expr->expression);
}

Object AstPrinter::oprtLiteral(Literal* expr) {
    return *expr->value;
}   

Object AstPrinter::oprtUnary(Unary* expr) {
    return parenthesize(expr->operatorr->lexeme, expr->right);
}

string AstPrinter::parenthesize(string name, Expr* expr) {
    string result;

    result.append("(").append(name);
    result.append(" ");
    result.append(objectToString(expr->accept(this)));
    result.append(")");

    return result;
}

string AstPrinter::parenthesize(string name, Expr* expr1, Expr* expr2) {
    string result;

    result.append("(").append(name);
    
    result.append(" ");
    result.append(objectToString(expr1->accept(this)));
    result.append(" ");
    result.append(objectToString(expr2->accept(this)));

    result.append(")");

    return result;
}

string AstPrinter::parenthesize(Expr* expr1, Expr* expr2, Expr* expr3) {
    string result;

    result.append("(").append("?:");
    
    result.append(" ");
    result.append(objectToString(expr1->accept(this)));
    result.append(" ");
    result.append(objectToString(expr2->accept(this)));
    result.append(" ");
    result.append(objectToString(expr3->accept(this)));

    result.append(")");

    return result;
}



