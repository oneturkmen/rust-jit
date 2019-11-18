#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <string>

#include "ast.hpp"
#include "ast_visitor.hpp"
#include "object.hpp"
#include "token.hpp" // TODO: remove this (used in visitLiteral)

// Forward declaration of classes for Christmas visit.
// class Expr;
// class Literal;
// class BinaryExpr;
// class UnaryExpr;
// class GroupingExpr;


/**
 * Driver class for interpretation (execution) of code.
 */
class Interpreter : ASTVisitor<Object*> {
    public:
        Interpreter() {
            // does nothing
        }

        Object* visitExpr(Expr* expr);
        Object* visitLiteral(Literal* literal);
        Object* visitBinaryExpr(BinaryExpr* bin_expr);
        Object* visitUnaryExpr(UnaryExpr* unary_expr);
        Object* visitGroupingExpr(GroupingExpr* group_expr);

        void interpret(Expr* expr);

    private:
        Object* evaluate(Expr* expr) {
            if (expr == nullptr) {
                std::cout << "Expr is nullptr\n";
            }
            std::cout << "Accepting expression in evaluate()\n";
            return expr->accept(this); 
        }
};

#endif
