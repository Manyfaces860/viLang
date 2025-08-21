
#include <string>
#include <vector>
#include "include/expr.h"
#include "include/oprt.h"
#include "include/allexpr.h"
#include "include/interpreter.h"
#include "include/util.h"
#include "include/stmt.h"
#include "include/allstmt.h"


using std::string, std::vector;

Interpreter::Interpreter() {}

Interpreter::Interpreter(vector<Stmt*> program) {
    this->program = program;
}

void Interpreter::interpret() {
    try {    
        for (Stmt* stmt : this->program) {
            execute(stmt);
        }
    } catch (RuntimeError error) {
        print(error.what());
    }
    return;
}

void Interpreter::execute(Stmt* stmt) {
    stmt->accept(this);
}

Object Interpreter::oprtVariable(Variable* expr) {
    return environment.get(*expr->name);
}

Object Interpreter::oprtVar(Var* stmt) {
    Token* name = stmt->name;
    Object value = evaluate(stmt->initializer);
    environment.define(name->lexeme, value);
    return nullptr;
}

Object Interpreter::oprtAssign(Assign* expr) {
    return nullptr; // no need to implement
}

Object Interpreter::oprtBlock(Block* stmt) {
    return nullptr; // wait for function implementation
}

Object Interpreter::oprtPrint(Print* stmt) {
    Object value = evaluate(stmt->expression);
    if (isFloat(value)) print(stripFloatZeroes(value));
    else print(objectToString(value));
    return nullptr;
}

Object Interpreter::oprtExpression(Expression* stmt) {
    evaluate(stmt->expression);
    return nullptr;
}

Object Interpreter::evaluate(Expr* expr) {
    return expr->accept(this);
}

Object Interpreter::oprtTernary(Ternary* expr) {
    Object left = evaluate(expr->left);
    if (isTruthy(left)) return evaluate(expr->middle);

    return evaluate(expr->right);
}

Object Interpreter::oprtBinary(Binary* expr) {
    Object left = evaluate(expr->left);
    Object right = evaluate(expr->right);

    switch (expr->operatorr->type)
    {
        case TokenType::MINUS:
            checkNumberOperands(*expr->operatorr, left, right);
            return getFloat(left) - getFloat(right);
        case TokenType::STAR:
            checkNumberOperands(*expr->operatorr, left, right);
            return getFloat(left) * getFloat(right);
        case TokenType::SLASH:
            checkNumberOperands(*expr->operatorr, left, right);
            return getFloat(left) / getFloat(right);
        case TokenType::PLUS:
            if (isFloat(left) && isFloat(right)) return getFloat(left) + getFloat(right);
            if (isString(left) && isString(right)) return getString(left) + getString(right);
            throw RuntimeError("Operands must be two numbers or two strings.", *expr->operatorr);
            
        case TokenType::GREATER:
            checkNumberOperands(*expr->operatorr, left, right);
            return getFloat(left) > getFloat(right);
        case TokenType::GREATER_EQUAL:
            checkNumberOperands(*expr->operatorr, left, right);
            return getFloat(left) >= getFloat(right);
        case TokenType::BANG_EQUAL: 
            return !isEqual(left, right);
        case TokenType::EQUAL_EQUAL:
            return isEqual(left, right);
        default:
            throw RuntimeError("Unknown Binary operator", *expr->operatorr);
    }

}

Object Interpreter::oprtGrouping(Grouping* expr) {
    return evaluate(expr->expression);
}

Object Interpreter::oprtLiteral(Literal* expr) {
    Object* a = expr->value;
    return *a;
}

Object Interpreter::oprtUnary(Unary* expr) {
    Object right = evaluate(expr->right);

    switch (expr->operatorr->type)
    {
        case TokenType::MINUS:
            checkNumberOperands(*expr->operatorr, right);
            return -getFloat(right);
        case TokenType::BANG: // can also implement not using the same code
            if (isTruthy(right)) return false;
            return true;
        default:
            throw RuntimeError("Unknown Unary operator", *expr->operatorr);
    }
}

bool Interpreter::isTruthy(Object& obj) {
    if (isFloat(obj)) return getFloat(obj) != 0;
    if (isString(obj)) return getString(obj) != "";
    if (isBool(obj)) return getBool(obj);
    if (isNull(obj)) return false;

    return true;
}

bool Interpreter::isEqual(Object& left, Object& right) {
    if (isFloat(left) && isFloat(right)) return getFloat(left) == getFloat(right);
    if (isString(left) && isString(right)) return getString(left) == getString(right);
    if (isBool(left) && isBool(right)) return getBool(left) == getBool(right);
    if (isNull(left) && isNull(right)) return true;
    
    return isTruthy(left) == isTruthy(right);
}

void Interpreter::checkNumberOperands(Token& operatorr, Object& left, Object& right) {
    if (isFloat(left) && isFloat(right)) return;
    throw RuntimeError("Operands must be two numbers", operatorr);
}

void Interpreter::checkNumberOperands(Token& operatorr, Object& right) {
    if (isFloat(right)) return;
    throw RuntimeError("Operand must be a number", operatorr);
}

void Interpreter::runInteractive(Stmt* stmt) {
    try { execute(stmt); }
    catch (RuntimeError error) { print(error.what()); }
    return;
}
