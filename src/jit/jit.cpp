#include "jit.hpp"

Object* Jit::visitExpr(Expr* expr) {
    return evaluate(expr);
}
