#pragma once
#include <iostream>
#include <string>
#include "token.h"
#include "exception.h"
#include "karanodak.h"

using std::string;


template <typename T>
void printOne(const T& value) {
    std::cout << value << std::endl;
}

template <typename T, typename... Args>
static void print(const T& first, const Args&... rest) {
    printOne(first);
    if constexpr (sizeof...(rest) > 0) print(rest...);
}

static string objectToString(const Object& obj) {
    if (std::holds_alternative<float>(obj)) {
        return std::to_string(std::get<float>(obj));
    }
    else if (std::holds_alternative<std::string>(obj)) {
        return std::get<std::string>(obj);
    }
    else if (std::holds_alternative<bool>(obj)) {
        return std::get<bool>(obj) ? "true" : "false";
    }
    else if (std::holds_alternative<nullptr_t>(obj)) {
        return "NOPE";
    }
    
    throw AstPrinterError("Unknown object type");
}

static bool isFloat(const Object& obj) {
    return std::holds_alternative<float>(obj);
}

static bool isString(const Object& obj) {
    return std::holds_alternative<string>(obj);
}

static bool isBool(const Object& obj) {
    return std::holds_alternative<bool>(obj);
}

static bool isNull(const Object& obj) {
    return std::holds_alternative<nullptr_t>(obj);
}

static float getFloat(const Object& obj) {
    return std::get<float>(obj);
}
static string getString(const Object& obj) {
    return std::get<string>(obj);
}
static bool getBool(const Object& obj) {
    return std::get<bool>(obj);
}
static nullptr_t getNull(const Object& obj) {
    return std::get<nullptr_t>(obj);
}

static std::shared_ptr<Karanodak> getCallable(const Object& obj) {
    if (auto ptr = std::get_if<std::shared_ptr<Karanodak>>(&obj)) {
        return *ptr;  // return the stored shared_ptr
    }
    throw RuntimeError("Object is not a callable!", getString(obj));
}

static string stripFloatZeroes(Object& num) {
    string str = objectToString(num);
    size_t index = str.find('.');
    if (index != string::npos) return str.substr(0, index);
    return "undefined";
}

static std::string expandTabs(const std::string& s, int tabsize = 2) {
    std::string result;
    int column = 0;

    for (char ch : s) {
        if (ch == '\t') {
            print("is tab");
            int spaces = tabsize - (column % tabsize);
            result.append(spaces, ' ');
            column += spaces;
        } else if (ch == '\n') {
            result.push_back(ch);
            column = 0;
        } else {
            result.push_back(ch);
            column++;
        }
    }

    return result;
}

static void clearNewLines(std::vector<Token>& tokens, int& current) {
    while (tokens[current].type == TokenType::NEW_LINE) {
        current++;
    }
}

static int indentation(std::vector<Token>& tokens, int &current) {
    int spaces = 0;
    clearNewLines(tokens, current);
    int previous = current;
    while (tokens[current].type == TokenType::SPACE) {
        spaces++;
        current++;
    }
    current = previous;
    return spaces;
}

static void consumeSpaces(std::vector<Token>& tokens, int& current) {
    while (tokens[current].type == TokenType::SPACE) {
        current++;
    }
}