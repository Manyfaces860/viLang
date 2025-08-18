#pragma once
#include <exception>
#include <string>
// fix inheriting from runtime error class std::runtime_error
class BaseException : public std::exception {

    std::string msg;
    
    public:
        explicit BaseException(std::string msg) : msg(std::move(msg)) {}
        
        const char* what() const noexcept override {
            return msg.c_str();
        }
};

class LexerException : public std::runtime_error{
    public:
        explicit LexerException(const std::string& msg) : std::runtime_error("LexerException: " + msg) {}
};

class ParserException : public std::runtime_error {
    public:
        explicit ParserException(const std::string& msg) : std::runtime_error("ParserException: " + msg) {}
};

class AstPrinterException : public std::runtime_error {
    public:
        explicit AstPrinterException(const std::string& msg) : std::runtime_error("AstPrinterException: " + msg) {}
};