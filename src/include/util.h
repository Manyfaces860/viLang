#pragma once
#include <iostream>
#include "token.h"
#include "exception.h"

template <typename T>

void print(T thing) {
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
    
    throw AstPrinterException("Unknown object type");
}