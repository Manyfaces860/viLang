#pragma once
#include <vector>
#include "token.h"

using std::vector;

class Interpreter;

class Karanodak {
    public:
        virtual Object __call__(Interpreter* runtime, vector<Object>* arguments) = 0;
        virtual Object __arity__() = 0;
        virtual Object __repr__() = 0;
        virtual ~Karanodak() noexcept(false) = default;
};