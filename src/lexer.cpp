#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <streambuf>
#include <unordered_map>
#include "include/util.h"
#include "include/lexer.h"
#include "include/token.h"

using std::string;

std::unordered_map<string, TokenType> Lexer::keywords = {
    {"and",    TokenType::AND},
    {"class",  TokenType::CLASS},
    {"else",   TokenType::ELSE},
    {"elif",   TokenType::ELIF},
    {"false",  TokenType::FALSE},
    {"for",    TokenType::FOR},
    {"def",    TokenType::DEF},
    {"if",     TokenType::IF},
    {"NOPE",    TokenType::NOPE},
    {"or",     TokenType::OR},
    {"print",  TokenType::PRINT},
    {"return", TokenType::RETURN},
    {"super",  TokenType::SUPER},
    {"this",   TokenType::THIS},
    {"true",   TokenType::TRUE},
    {"while",  TokenType::WHILE},
    {"in",     TokenType::IN},
    {"is",     TokenType::IS}
};

Lexer::Lexer(string source) {
    this->source = source;
}

Lexer::Lexer() {}

void Lexer::getSourceContent() {
    std::ifstream file(Lexer::source, std::ios::binary);

    std::string content{ 
        std::istreambuf_iterator<char>(file), {} 
    };

    this->content = content;
}   


void Lexer::tokenize() {

    while (!atEnd()) {

        start = current;
        scanToken();
    }
    while (tokens.back().type == TokenType::SPACE) tokens.pop_back();
    Lexer::tokens.push_back(Token(TokenType::ENDOFFILE, "", "", line));
}       

bool Lexer::atEnd() {
    return current >= content.length();
}

char Lexer::next() {
    return content[current++];
}

void Lexer::scanToken() {
    char c = next();

    switch (c) {
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break;
        case '?': addToken(TokenType::QUESTION_MARK); break;
        case ':': addToken(TokenType::COLON); break;
        case '!':
            match('=') ? addToken(TokenType::BANG_EQUAL) : addToken(TokenType::BANG);
            break;
        case '=':
            match('=') ? addToken(TokenType::EQUAL_EQUAL) : addToken(TokenType::EQUAL);
            break;
        case '<':
            match('=') ? addToken(TokenType::LESS_EQUAL) : addToken(TokenType::LESS);
            break;
        case '>':
            match('=') ? addToken(TokenType::GREATER_EQUAL) : addToken(TokenType::GREATER);
            break;
        case '/':
            if (match('/')) {
                while (peek() != '\n' && !atEnd()) {
                    next();
                }
            } else {
                addToken(TokenType::SLASH);
            }
            break;
        case ' ':
            if (!hit) addToken(TokenType::SPACE);
        case '\r':
        case '\t':
            break;
        case '\n':
            if (tokens.size() > 0) while (tokens.back().type == TokenType::SPACE) tokens.pop_back();
            addToken(TokenType::NEW_LINE);
            hit = false;
            line++;
            break;
        case '"':
            stringLiterals();
            break;
        default:
            if (isDigit(c)) {
                number();
            } 
            else if (isAlpha(c)) {
                identifier();
            }
            else {
                LexerError("Unexpected character '" + std::to_string(c) + "' at " + std::to_string(line) + ".");
            }
            break;

    }
}

void Lexer::addToken(TokenType type) {
    if (type != TokenType::SPACE && type != TokenType::NEW_LINE) hit = true;  
    addToken(type, "");
}

void Lexer::addToken(TokenType type, Object literal) {
    string lexeme = content.substr(start, current - start);
    tokens.push_back(Token(type, lexeme, literal, line));
}

bool Lexer::match(char expected) {
    if (atEnd()) return false;
    if (content[current] != expected) return false;

    current++;
    return true;
}

char Lexer::peek() {
    if (atEnd()) return '\0';
    return content[current];
}

void Lexer::stringLiterals() {
    int currentLine = line;
    while (peek() != '"' && !atEnd()) {
        if (peek() == '\n') line++;
        next();
    }

    if (atEnd()) {
        throw LexerError("Unterminated string at " + std::to_string(currentLine) + ".");
        return;
    }

    next();

    string literal = content.substr(start+1, current-start-2);
    addToken(TokenType::STRING, literal);
}

void Lexer::number() {
    while (isDigit(peek())) next();

    if (peek() == '.' && isDigit(peekNext())) next();
    
    while (isDigit(peek())) next();

    Object literal = std::stof(content.substr(start, current-start));

    addToken(TokenType::NUMBER, literal);
}

bool Lexer::isDigit(char c) {
    return c >= '0' && c <= '9';
}

char Lexer::peekNext() {
    if (current + 1 >= content.length()) return '\0';
    return content[current + 1];
}

std::vector<Token> Lexer::getTokens() {
    return this->tokens;
}

void Lexer::identifier() {
    while (isAlphaNumeric(peek())) next();

    string iden = content.substr(start, current-start);

    TokenType type = keywords.find(iden) != keywords.end() ? keywords[iden] : TokenType::IDENTIFIER;

    addToken(type);
}

bool Lexer::isAlpha(char c) {
    if (c >= 'a' && c <= 'z') return true;
    if (c >= 'A' && c <= 'Z') return true;
    if (c == '_') return true;
    return false;
}

bool Lexer::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

void Lexer::readygo() {
    getSourceContent();
    tokenize();
}

void Lexer::reset() {
    tokens.clear();
    current = 0;
    line = 1;
    start = 0;
}

void Lexer::setContent(string content) {
    this->content = content;
}

void Lexer::runInteractive(string content) {
    reset();
    setContent(content);
    tokenize();
}

void Lexer::printTokens(int count) {
    for (int i = 0; i < count; i++) {
        print(this->tokens[i].toString());
    }
}

void Lexer::printTokens() {
    for (int i = 0; i < tokens.size(); i++) {
        print(this->tokens[i].toString());
    }
}
