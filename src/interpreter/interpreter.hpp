#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <string>
#include <vector>

#include "ast.hpp"
#include "ast_visitor.hpp"
#include "environment.hpp"
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

        Object* visitVarDeclStmt(VarDeclStmt* varDeclStmt);
        Object* visitExprStmt(ExprStmt* exprStmt);
        Object* visitPrintStmt(PrintStmt* printStmt);
        Object* visitExpr(Expr* expr);
        Object* visitAssignExpr(AssignExpr* assign_expr);
        Object* visitIdentifier(Identifier* identifier);
        Object* visitLiteral(Literal* literal);
        Object* visitBinaryExpr(BinaryExpr* bin_expr);
        Object* visitUnaryExpr(UnaryExpr* unary_expr);
        Object* visitGroupingExpr(GroupingExpr* group_expr);

        void interpret(std::vector<Stmt*> expr);

    private:
        void execute(Stmt* stmt) {
            stmt->accept(this);
        }

        Object* evaluate(Expr* expr) {
            if (expr == nullptr) {
                std::cout << "Expr is nullptr\n";
            }
            std::cout << "Accepting expression in evaluate()\n";
            return expr->accept(this);
        }

    private:
        Environment env;
};

#endif
