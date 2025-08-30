
#include <string>
#include <vector>
#include "include/expr.h"
#include "include/oprt.h"
#include "include/allexpr.h"
#include "include/interpreter.h"
#include "include/util.h"
#include "include/stmt.h"
#include "include/allstmt.h"
#include "include/callables.h"
#include "include/exception.h"


using std::string, std::vector;

Interpreter::Interpreter() {}

Interpreter::Interpreter(vector<Stmt*> program) {
    this->program = program;
    setClock();
}

void Interpreter::interpret() {
    try {    
        for (Stmt* stmt : this->program) {
            // print("h");
            // if (Function* f = dynamic_cast<Function*>(stmt)) print("function");
            // if (Block* f = dynamic_cast<Block*>(stmt)) print("block");
            // if (If* f = dynamic_cast<If*>(stmt)) print("If");
            // if (While* f = dynamic_cast<While*>(stmt)) print("While");
            // if (Wcall* f = dynamic_cast<Wcall*>(stmt)) print("Wcall");
            // if (Var* f = dynamic_cast<Var*>(stmt)) print("Var");
            // if (Print* f = dynamic_cast<Print*>(stmt)) print("Print");
            // if (Expression* f = dynamic_cast<Expression*>(stmt)) print("Expression");
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
    return this->globals->get(*expr->name);
}

Object Interpreter::oprtVar(Var* stmt) {
    Token* name = stmt->name;
    Object value = evaluate(stmt->initializer);
    globals->define(name->lexeme, value);
    return nullptr;
}

Object Interpreter::oprtAssign(Assign* expr) {
    return nullptr; // no need to implement
}

Object Interpreter::oprtBlock(Block* stmt) {
    for (Stmt* statement : stmt->statements) {
        execute(statement);
    }
    return nullptr;
}

Object Interpreter::oprtIf(If* stmt) {
    Object condition = evaluate(stmt->condition);
    if (isTruthy(condition)) {
        execute(stmt->thenBranch);
    }
    else {
        bool matched = false;
        for (auto& [k, v] : stmt->elifBranches) {
            Object elifCondition = evaluate(k);
            if (isTruthy(elifCondition)) {
                execute(v);
                matched = true;
                break;
            }
        }
        if (!matched && stmt->elseBranch != nullptr) execute(stmt->elseBranch);
    }
    return nullptr;
}

Object Interpreter::oprtLogical(Logical* expr) {
    Object left = evaluate(expr->left);
    if (expr->operatorr->type == TokenType::AND) {
        if (!isTruthy(left)) return isTruthy(left);
    } 
    else {
        if (isTruthy(left)) return isTruthy(left);
    }
    return isTruthy(evaluate(expr->right));
}

Object Interpreter::oprtWhile(While* stmt) {
    while (isTruthy(evaluate(stmt->condition))) execute(stmt->body);
    return nullptr;
}

Object Interpreter::oprtWcall(Wcall* stmt) {
    return evaluate(stmt->callExpr);
}

Object Interpreter::oprtCall(Call* expr) {
    Object callee = evaluate(expr->callee);
    vector<Object> arguments;
    for (Expr* arg : expr->arguments) arguments.push_back(evaluate(arg));
    std::shared_ptr<Karanodak> function = getCallable(callee);
    
    Object value = nullptr;
    value = function->__call__(this, &arguments);
    return value;
}

Object Interpreter::oprtFunction(Function* stmt) {
    std::shared_ptr<Karanodak> function = std::make_shared<ViFunction>(stmt, this->globals);
    this->globals->define(stmt->name->lexeme, function);
    return nullptr;
}

Object Interpreter::oprtReturn(Return* stmt) {
    Object value = evaluate(stmt->value);
    throw ReturnV(value);
    return nullptr;
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
        case TokenType::LESS:
            checkNumberOperands(*expr->operatorr, left, right);
            return getFloat(left) < getFloat(right);
        case TokenType::LESS_EQUAL:
            checkNumberOperands(*expr->operatorr, left, right);
            return getFloat(left) <= getFloat(right);
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

bool Interpreter::isTruthy(const Object& obj) {
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

Object Interpreter::getGlobal(Token* token) {
    return this->globals->get(*token);
}

Environment* Interpreter::getGlobals() {
    return this->globals;
}

void Interpreter::setEnvironment(Environment* scope) {
    this->globals = scope;
}

void Interpreter::setClock() {
    this->globals->define("clock", std::make_shared<Clock>());
}