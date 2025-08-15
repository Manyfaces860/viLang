#pragma once
#include "expr.h"
#include "oprt.h"
#include "allexpr.h"
#include <string>

using std::string;


template <typename T>
class AstPrinter : public Oprt<T> {
    public:

        string print(Expr<T>* expr) {
            return expr->accept(this);
        }
        
        T oprtBinary(Binary<T>* expr) override {
            return parenthesize(expr->operatorr->lexeme,
                        expr->left, expr->right);
        }

        T oprtGrouping(Grouping<T>* expr) override {
            return parenthesize("group", expr->expression);
        }

        T oprtLiteral(Literal<T>* expr) override {
            if (std::holds_alternative<float>(*expr->value)) {
                return std::to_string(std::get<float>(*expr->value));
            } else if (std::holds_alternative<string>(*expr->value)) {
                return std::get<string>(*expr->value);
            }
            return "";
        }   

        T oprtUnary(Unary<T>* expr) override {
            return parenthesize(expr->operatorr->lexeme, expr->right);
        }

    private:
        string parenthesize(string name, Expr<T>* expr) {
            string result;

            result.append("(").append(name);
            result.append(" ");
            result.append(expr->accept(this));
            result.append(")");

            return result;
        }

        string parenthesize(string name, Expr<T>* expr1, Expr<T>* expr2) {
            string result;

            result.append("(").append(name);
            
            result.append(" ");
            result.append(expr1->accept(this));
            result.append(" ");
            result.append(expr2->accept(this));

            result.append(")");

            return result;
        }

};
