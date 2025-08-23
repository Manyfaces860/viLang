
#include <vector>
#include <utility>
#include "include/token.h"
#include "include/allexpr.h"
#include "include/parser.h"
#include "include/exception.h"
#include "include/allstmt.h"
#include "include/util.h"

using std::string, std::vector;

Parser::Parser(std::vector<Token> tokens) {
    this->tokens = tokens;
}

Parser::Parser() {}

vector<Stmt*> Parser::parse() {
    vector<Stmt*> statements;
    while (consumeSpacesAndNewLinesForTop() && !atEnd()) {
        statements.push_back(declaration());
    }

    return statements;
}

Stmt* Parser::declaration() {
    try {
        if (peek()->type == TokenType::IDENTIFIER) {
            Expr* expr = expression();
            if (Assign* assignExpr = dynamic_cast<Assign*>(expr)) {
                return new Var(assignExpr->name, assignExpr->value);
            }
        }
        return statement();
    } catch (ParserError error) {
        // synchronize();
        throw error;
        return nullptr;
    }
}

void Parser::synchronize() {
    return;
}

Expr* Parser::assignment() { 
    Expr* expr = logicOr();

    if (match(TokenType::EQUAL)) {
        Token* equals = previous();
        Expr* value = assignment();
        
        if (Variable* identifier = dynamic_cast<Variable*>(expr)) {
            Token* name = identifier->name;
            if (isOnNextLine()) return new Assign(name, value);
        }
        throw ParserError("Invalid assignment target.", *equals);
    }

    return expr;
}

Expr* Parser::logicOr() {
    Expr* left = logicAnd();

    while (match(TokenType::OR)) {
        Token* operatorr = previous();
        Expr* right = logicAnd();
        left = new Logical(left, operatorr, right);
    }

    return left;
}

Expr* Parser::logicAnd() {
    Expr* left = equality();

    while (match(TokenType::AND)) {
        Token* operatorr = previous();
        Expr* right = equality();
        left = new Logical(left, operatorr, right);
    }

    return left;
}

Stmt* Parser::statement() {
    if (match(TokenType::PRINT)) return printStatement();
    if (match(TokenType::IF)) return ifStatement();

    return expressionStatement();
}

Stmt* Parser::ifStatement() {
    Expr* condition = expression();
    consume(TokenType::COLON, "Expected ':' after condition");
    Stmt* thenBranch = blockStatement();
    
    bool indentMatch = false;
    std::vector<std::pair<Expr*, Stmt*>> elifBranches;
    if (this->indent == indentation(tokens, current)) {
        do {
            consumeSpaces(tokens, current);
            indentMatch = true;
            if (match(TokenType::ELIF)) {
                Expr* elCondition = expression();
                consume(TokenType::COLON, "Expected ':' after elif");
                Stmt* elBranch = blockStatement();
                elifBranches.push_back({elCondition, elBranch});
            } else break;
        }
        while (this->indent == indentation(tokens, current));
    }
    
    Stmt* elseBranch = nullptr;
    if (indentMatch || this->indent == indentation(tokens, current)) {
        if (match(TokenType::ELSE)) {
            consume(TokenType::COLON, "Expected ':' after else");
            elseBranch = blockStatement();
        }
    }
    return new If(condition, thenBranch, elifBranches, elseBranch);
}

Stmt* Parser::blockStatement() {
    vector<Stmt*> statements = block();
    return new Block(statements);
}

vector<Stmt*> Parser::block() {
    int previous = this->indent;

    int count = indentation(tokens, current);
    this->indent = count > this->indent ? count : throw ParserError("indentation error", *peek());
    
    int spaces = this->indent;
    vector<Stmt*> statements;

    do {
        consumeSpaces(tokens, current);
        statements.push_back(declaration());
        spaces = indentation(tokens, current);
    } while (this->indent == spaces);

    this->indent = previous;
    return statements;
}

Stmt* Parser::printStatement() {
    if (match(TokenType::LEFT_PAREN)) {
        Expr* value = expression();
        consume(TokenType::RIGHT_PAREN, "Expected ')' after expression.");
        if (isOnNextLine()) return new Print(value); 
    }
    throw ParserError("Expected '(' after 'print'.", *peek());
}

Stmt* Parser::expressionStatement() {
    Expr* expr = expression();
    if (isOnNextLine()) return new Expression(expr);
    return nullptr;
}

Expr* Parser::expression() {
    return assignment();
}

Expr* Parser::equality() {
    Expr* left = comparison();

    while (match({ TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL })) {
        Token* operatorr = previous();
        Expr* right = comparison();
        left = new Binary(left, operatorr, right);
    }
    if (match( TokenType::QUESTION_MARK )) {
        Expr* middle = expression();
        if (match(TokenType::COLON)) {
            Expr* right = expression();
            left = new Ternary(left, middle, right);
        } else {
            throw ParserError("Expected ':' after expression.", *peek());
        }
    }

    return left;
}

Expr* Parser::comparison() {
    Expr* left = term();

    while (match({ TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL })) {
        Token* operatorr = previous();
        Expr* right = term();
        left = new Binary(left, operatorr, right);
    }
    return left;
}

Expr* Parser::term() {
    Expr* left = factor();

    while (match({ TokenType::MINUS, TokenType::PLUS })) {
        Token* operatorr = previous();
        Expr* right = factor();
        left = new Binary(left, operatorr, right);
    }
    return left;
}

Expr* Parser::factor() {
    Expr* left = unary();

    while (match({ TokenType::SLASH, TokenType::STAR })) {
        Token* operatorr = previous();
        Expr* right = unary();
        left = new Binary(left, operatorr, right);
    }
    return left;
}

Expr* Parser::unary() {
    if (match({ TokenType::BANG, TokenType::MINUS })) {
        Token* operatorr = previous();
        Expr* right = unary();
        return new Unary(operatorr, right);
    }
    return primary();
}

Expr* Parser::primary() {
    if (match({ TokenType::NUMBER, TokenType::STRING })) return new Literal(&previous()->literal);
    if (match(TokenType::TRUE)) return new Literal(new Object(true));
    if (match(TokenType::FALSE)) return new Literal(new Object(false));
    if (match(TokenType::NOPE)) return new Literal(new Object(nullptr));
    if (match( TokenType::LEFT_PAREN )) {
        Expr* expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expected ')' after expression.");
        return new Grouping(expr);
    }
    if (match(TokenType::IDENTIFIER)) return new Variable(previous());
    throw ParserError("Expected Literal or Variable", *peek());
}

vector<Stmt*> Parser::runInteractive(std::vector<Token> tokens) {
    this->tokens = tokens;
    this->current = 0;
    return parse();
}

Token* Parser::consume(TokenType type, string message) {
    if (check(type)) return next();
    
    throw ParserError(message);
}

void Parser::consume(TokenType type) {
    if (check(type)) next();
}

bool Parser::match(std::vector<TokenType> types) {
    for (TokenType type : types) {
        if (check(type)) {
            next();
            return true;
        }
    }
    return false;
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        next();
        return true;
    }
    return false;
}

bool Parser::check(TokenType type) {
    if (atEnd()) return false;
    return peek()->type == type;
}

Token* Parser::next() {
    if (!atEnd()) this->current++;
    return previous();
}

bool Parser::atEnd() {
    return peek()->type == TokenType::ENDOFFILE;
}

Token* Parser::peek() {
    return &this->tokens[current];
}

Token* Parser::peekNext() {
    return &this->tokens[current+1];
}

Token* Parser::previous() {
    return &this->tokens[current-1];
}

bool Parser::isOnNextLine() {
    if (peek()->type != TokenType::NEW_LINE && peek()->type != TokenType::ENDOFFILE) throw ParserError("Expected newline or end of file or statements should be seperated by newline.", *peek());
    consume(TokenType::NEW_LINE);
    return true;
}

bool Parser::consumeSpacesAndNewLinesForTop() {
    if (this->indent == 0) {
        clearNewLines(tokens, current);
        consumeSpaces(tokens, current);
    }
    return true;
}