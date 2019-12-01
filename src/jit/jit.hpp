#ifndef JIT_H
#define JIT_H

#include <iostream>
#include <string>
#include <vector>

#include "JitBuilder.hpp"

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

static void printNumber(int val) {
    printf("%d", val);
}


/**
 * Helper class for JIT compilation. Extends MethodBuilder.
 * In other words, contains IR for some stmt, at a time.
 */
class StatementBuilder : public OMR::JitBuilder::MethodBuilder {
    public:
        StatementBuilder(OMR::JitBuilder::TypeDictionary* types);

        virtual bool buildIL() override;
};


/**
 * Driver class for JIT compilation of code.
 */
class Jit : ASTVisitor<OMR::JitBuilder::IlValue*> {
    public:
        Jit() {
            // does nothing
            bool initialized = initializeJit();
            if (!initialized) {
                std::cout << "FAIL: could not initialize JIT\n";
                exit(-1);
            }
        }

        OMR::JitBuilder::IlValue* visitVarDeclStmt(VarDeclStmt* varDeclStmt);
        OMR::JitBuilder::IlValue* visitExprStmt(ExprStmt* exprStmt);
        OMR::JitBuilder::IlValue* visitPrintStmt(PrintStmt* printStmt);
        OMR::JitBuilder::IlValue* visitExpr(Expr* expr);
        OMR::JitBuilder::IlValue* visitAssignExpr(AssignExpr* assign_expr);
        OMR::JitBuilder::IlValue* visitIdentifier(Identifier* identifier);
        OMR::JitBuilder::IlValue* visitLiteral(Literal* literal);
        OMR::JitBuilder::IlValue* visitBinaryExpr(BinaryExpr* bin_expr);
        OMR::JitBuilder::IlValue* visitUnaryExpr(UnaryExpr* unary_expr);
        OMR::JitBuilder::IlValue* visitGroupingExpr(GroupingExpr* group_expr);

        void compile(std::vector<Stmt*> stmts);

    private:
        void execute(Stmt* stmt) {
            stmt->accept(this);
        }

        OMR::JitBuilder::IlValue* evaluate(Expr* expr) {
            if (expr == nullptr) {
                std::cout << "Expr is nullptr\n";
            }
            std::cout << "Accepting expression in evaluate()\n";
            return expr->accept(this);
        }

        // OMR IR builder per stmt
        OMR::JitBuilder::IlBuilder il;
};

#endif
