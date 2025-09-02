#pragma once
#include <vector>
#include "implemented.h"

using std::vector;


class Clock : public ViCallable {
    public:
        Object __call__(Interpreter* runtime, vector<Object>* arguments) override;
        Object __arity__() override;
        Object __repr__() override;
};

class Range : public ViCallable {
    public:
        Object __call__(Interpreter* runtime, vector<Object>* arguments) override;
        Object __arity__() override;
        Object __repr__() override;
};

