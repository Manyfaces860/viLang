#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "token.h"

using std::string;

class Lexer {
    private:
        std::vector<Token> tokens;
        string source;
        string content;
        int current = 0;
        int line = 1;
        int start = 0;
        bool hit = false;

        static std::unordered_map<string, TokenType> keywords;

        void getSourceContent();
        
        void tokenize();

        bool atEnd();

        char next();

        void scanToken();

        void addToken(TokenType type);

        void addToken(TokenType type, Object literal);

        bool match(char expected);

        char peek();

        void stringLiterals();

        void number();

        bool isDigit(char c);

        char peekNext();

        void identifier();

        bool isAlpha(char c);

        bool isAlphaNumeric(char c);
        
        void reset();

        void setContent(string content);

    public:
        Lexer(string source); 

        Lexer(); 
        
        void readygo();

        void runInteractive(string content);

        void printTokens(int count);

        void printTokens();

        std::vector<Token> getTokens();
};
