#pragma once
#include <iostream>
#include <string>
#include "token.h"
#include "exception.h"

using std::string;

template <typename T>

static void print(T thing) {
    std::cout << thing << std::endl;
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

static bool isFloat(Object& obj) {
    return std::holds_alternative<float>(obj);
}

static bool isString(Object& obj) {
    return std::holds_alternative<string>(obj);
}

static bool isBool(Object& obj) {
    return std::holds_alternative<bool>(obj);
}

static bool isNull(Object& obj) {
    return std::holds_alternative<nullptr_t>(obj);
}

static float getFloat(Object& obj) {
    return std::get<float>(obj);
}
static string getString(Object& obj) {
    return std::get<string>(obj);
}
static bool getBool(Object& obj) {
    return std::get<bool>(obj);
}
static nullptr_t getNull(Object& obj) {
    return std::get<nullptr_t>(obj);
}

static string stripFloatZeroes(Object& num) {
    string str = objectToString(num);
    size_t index = str.find('.');
    if (index != string::npos) return str.substr(0, index);
    return "undefined";
}
