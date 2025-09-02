#pragma once
#include <vector>
#include "token.h"
#include "allexpr.h"
#include "stmt.h"

using std::vector;

class Parser {
    public:
        vector<Token> tokens;
        int current = 0;
        int indent = 0;
        int nextIndent = 0;
        bool sameLevelBlockExit = false;

        Parser(vector<Token> tokens);
        Parser();
        vector<Stmt*> parse();
        Stmt* statement();
        Stmt* declaration();
        vector<Stmt*> runInteractive(vector<Token> tokens);

    private:
        Expr* assignment();
        void synchronize();
        Expr* logicOr();
        Expr* logicAnd();
        Stmt* printStatement();
        Stmt* blockStatement();
        Stmt* ifStatement();
        Stmt* whileStatement();
        Stmt* functionStatement(string kind);
        Stmt* returnStatement();
        Stmt* classStatement();
        Stmt* expressionStatement();
        Expr* expression();
        Expr* equality();
        Expr* comparison();
        Expr* term();
        Expr* factor();
        Expr* unary();
        Expr* call();
        Expr* finishCall(Expr* expr);
        Expr* primary();
        Token* consume(TokenType type, string message);
        void consume(TokenType type);
        bool match(vector<TokenType> types);
        bool match(TokenType type);
        bool check(TokenType type);
        Token* next();
        bool atEnd();
        Token* peek();
        Token* peekNext();
        Token* previous();
        bool isOnNextLine();
        vector<Stmt*> block();
        bool consumeSpacesAndNewLinesForTop();
        void error(string msg, Token* token);

};
