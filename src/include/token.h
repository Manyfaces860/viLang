#pragma once
#include <iostream>
#include <variant>
#include <string>


using std::string;

enum class TokenType {
  // Single-character tokens.
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR, COLON,
  QUESTION_MARK,

  // One or two character tokens.
  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // Literals.
  IDENTIFIER, STRING, NUMBER,

  // Keywords.
  AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NOPE, OR,
  PRINT, RETURN, SUPER, THIS, TRUE, WHILE,

  ENDOFFILE
};

using Object = std::variant<float, string, bool, nullptr_t>;

class Token {

  public: 
    TokenType type;
    string lexeme;
    Object literal;
    int line; 

    Token(TokenType type, string lexeme, Object literal, int line) 
    : type(type), lexeme(std::move(lexeme)), literal(std::move(literal)), line(line) {}

    string toString() const {
        return tokenTypeToString(type) + " " + lexeme + " " + objectToString(literal);
    }

  private:
    static string tokenTypeToString(TokenType t) {
      switch (t) {
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
        case TokenType::COMMA: return "COMMA";
        case TokenType::DOT: return "DOT";
        case TokenType::MINUS: return "MINUS";
        case TokenType::PLUS: return "PLUS";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::SLASH: return "SLASH";
        case TokenType::STAR: return "STAR";
        case TokenType::COLON: return "COLON";
        case TokenType::BANG: return "BANG";
        case TokenType::BANG_EQUAL: return "BANG_EQUAL";
        case TokenType::EQUAL: return "EQUAL";
        case TokenType::EQUAL_EQUAL: return "EQUAL_EQUAL";
        case TokenType::GREATER: return "GREATER";
        case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";
        case TokenType::LESS: return "LESS";
        case TokenType::LESS_EQUAL: return "LESS_EQUAL";
        case TokenType::QUESTION_MARK: return "QUESTION_MARK";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::STRING: return "STRING";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::AND: return "AND";
        case TokenType::CLASS: return "CLASS";
        case TokenType::ELSE: return "ELSE";
        case TokenType::FALSE: return "FALSE";
        case TokenType::FUN: return "FUN";
        case TokenType::FOR: return "FOR";
        case TokenType::IF: return "IF";
        case TokenType::NOPE: return "NOPE";
        case TokenType::OR: return "OR";
        case TokenType::PRINT: return "PRINT";
        case TokenType::RETURN: return "RETURN";
        case TokenType::SUPER: return "SUPER";
        case TokenType::THIS: return "THIS";
        case TokenType::TRUE: return "TRUE";
        case TokenType::WHILE: return "WHILE";
        case TokenType::ENDOFFILE: return "ENDOFFILE";
        default: return "UNKNOWN";
      }
    }

    static string objectToString(const Object &obj) {
        if (std::holds_alternative<float>(obj)) {
            return std::to_string(std::get<float>(obj));
        } else if (std::holds_alternative<string>(obj)) {
            return std::get<string>(obj);
        }
        return "";
    }
};

