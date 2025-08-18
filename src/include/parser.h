#pragma once
#include <vector>
#include "token.h"
#include "allexpr.h"


class Parser {
    public:
        std::vector<Token> tokens;
        int current = 0;

        Parser(std::vector<Token> tokens);
        Parser();
        Expr* parse();
        Expr* runInteractive(std::vector<Token> tokens);

    private:
        Expr* expression();
        Expr* equality();
        Expr* comparison();
        Expr* term();
        Expr* factor();
        Expr* unary();
        Expr* primary();
        bool match(std::vector<TokenType> types);
        bool match(TokenType type);
        bool check(TokenType type);
        Token* next();
        bool atEnd();
        Token* peek();
        Token* previous();

};
