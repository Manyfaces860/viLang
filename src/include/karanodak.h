#pragma once
#include <vector>
#include "token.h"

using std::vector;

class Interpreter;

class Karanodak {
    public:
        virtual Object __repr__() = 0;
        virtual ~Karanodak() noexcept(false) = default;
};