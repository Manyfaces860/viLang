// element base class
#pragma once
#include "oprt.h"

class Expr {
    public:
        virtual Object accept(Oprt* oprt) = 0;
        virtual ~Expr() noexcept(false) = default;
};

