#pragma once
#include "karanodak.h"

using std::vector;

class ViCallable : public Karanodak {
    public:
        virtual Object __call__(Interpreter* runtime, vector<Object>* arguments) = 0;
        virtual Object __arity__() = 0;
        virtual Object __repr__() = 0;
};

