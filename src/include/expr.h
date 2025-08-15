// element base class
#pragma once
#include "oprt.h"

template <typename T>
class Expr {
    public:
        virtual T accept(Oprt<T>* oprt) = 0;
        virtual ~Expr() noexcept(false) = default;
};

