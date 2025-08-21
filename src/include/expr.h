#pragma once
#include "token.h"
class Oprt;

class Expr {
    public:
        virtual Object accept(Oprt* oprt) = 0;
        virtual ~Expr() noexcept(false) = default;
};
