#include <iostream>
#pragma once

using std::string;

enum class TokenType {
  // Single-character tokens.
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

  // One or two character tokens.
  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // Literals.
  IDENTIFIER, STRING, NUMBER,

  // Keywords.
  AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

  EOFF
};

template <typename Object>

class Token {

  TokenType type;
  string lexeme;
  Object literal;
  int line; 

  public: Token(TokenType type, string lexeme, Object literal, int line) {
    type = type;
    lexeme = lexeme;
    literal = literal;
    line = line;
  }

  public: string toString() {
    return type + " " + lexeme + " " + literal;
  }
};

