#pragma once
#include <unordered_map>
#include "token.h"
#include "exception.h"
using std::string, std::vector;


class Environment {
    private:
        std::unordered_map<string, Object> values;
        Environment* enclosing;

    public:

        Environment() {
            enclosing = nullptr;
        }

        Environment(Environment* enclosing) {
            this->enclosing = enclosing;
        }

        void define(string name, Object value) {
            values[name] = value;
        }

        Object get(Token& token) {
            if (values.find(token.lexeme) == values.end()) {
                if (enclosing != nullptr) return enclosing->get(token);
                throw RuntimeError("Undefined variable", token);
            }

            return values[token.lexeme];
        }

        


};