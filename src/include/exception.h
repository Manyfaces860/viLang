#pragma once
#include <exception>
#include <string>

class CompileError : public std::exception {

    std::string msg;
    
    public:
        explicit CompileError(std::string msg) : msg(std::move(msg)) {}
        
        const char* what() const noexcept override {
            return msg.c_str();
        }
};

// compile time errors
class LexerError : public CompileError{
    public:
        explicit LexerError(const std::string& msg, const Token& token) : CompileError(msg + " at line " + std::to_string(token.line) + "with token " + token.lexeme) {}
};

class ParserError : public CompileError {
    public:
        explicit ParserError(const std::string& msg, const Token& token) : CompileError(msg + " at line " + std::to_string(token.line) + "with token " + token.lexeme) {}
        explicit ParserError(const std::string& msg) : CompileError(msg) {}
};

class AstPrinterError : public CompileError {
    public:
        explicit AstPrinterError(const std::string& msg) : CompileError(msg) {}
};


// runtime errors
class RuntimeError : public std::runtime_error {
    public:
        explicit RuntimeError(const std::string& msg, const Token& token) : std::runtime_error(msg + " at line " + std::to_string(token.line) + "with token " + token.lexeme) {}
};