
#include <vector>
#include "include/token.h"
#include "include/allexpr.h"
#include "include/parser.h"
#include "include/exception.h"

using std::string;

Parser::Parser(std::vector<Token> tokens) {
    this->tokens = tokens;
}

Parser::Parser() {}

Expr* Parser::parse() {
    return expression();
}

Expr* Parser::expression() {
    return equality();
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
            throw ParserException("Expected ':' after expression.");
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
        if (match( TokenType::RIGHT_PAREN )) {
            return new Grouping(expr);
        } else {
            throw ParserException("Expected ')' after expression.");
        }
    }
    throw ParserException("Expected Literal.");
    return nullptr;
}

Expr* Parser::runInteractive(std::vector<Token> tokens) {
    this->tokens = tokens;
    this->current = 0;
    return expression();
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

Token* Parser::previous() {
    return &this->tokens[current-1];
}