#pragma once
#include "token.h"
class OprtStmt;

class Stmt {
    public:
        virtual Object accept(OprtStmt* oprt) = 0;
        virtual ~Stmt() noexcept(false) = default;
};
