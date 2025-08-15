#pragma once
#include "expr.h"

template <typename T> class Binary;
template <typename T> class Grouping;
template <typename T> class Literal;
template <typename T> class Unary;


template <typename T>
class Oprt {
    public:
        virtual T oprtBinary(Binary<T>* expr) = 0;
        virtual T oprtGrouping(Grouping<T>* expr) = 0;
        virtual T oprtLiteral(Literal<T>* expr) = 0;
        virtual T oprtUnary(Unary<T>* expr) = 0;
        virtual ~Oprt() noexcept(false) = default;
};

