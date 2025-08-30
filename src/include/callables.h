#pragma once
#include <vector>
#include "karanodak.h"


using std::vector;

class Function;
class Environment;

class Clock : public Karanodak {
    public:
        Object __call__(Interpreter* runtime, vector<Object>* arguments) override;
        Object __arity__() override;
        Object __repr__() override;
};

class ViFunction : public Karanodak {

    public:
        Function* declaration;
        Environment* closure;

        ViFunction(Function* declaration, Environment* closure);
        Object __call__(Interpreter* runtime, vector<Object>* arguments) override;
        Object __arity__() override;
        Object __repr__() override;
};

class Range : public Karanodak {
    public:
        Object __call__(Interpreter* runtime, vector<Object>* arguments) override;
        Object __arity__() override;
        Object __repr__() override;
};

