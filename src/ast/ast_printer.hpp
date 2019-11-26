#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include <string>

#include "ast_visitor.hpp"
#include "ast.hpp"


class ASTPrinter: public ASTVisitor<std::string> {
    public:
        std::string visitVarDeclStmt(VarDeclStmt *varDeclStmt);
        std::string visitExprStmt(ExprStmt *exprStmt);
        std::string visitPrintStmt(PrintStmt *printStmt);
        std::string visitExpr(Expr* expr);
        std::string visitAssignExpr(AssignExpr* assign_expr);
        std::string visitIdentifier(Identifier* identifier);
        std::string visitLiteral(Literal* literal);
        std::string visitBinaryExpr(BinaryExpr* bin_expr);
        std::string visitUnaryExpr(UnaryExpr* unary_expr);
        std::string visitGroupingExpr(GroupingExpr* group_expr);

        // For testing only
        std::string print(Expr* expr) {
            return expr->accept(this);
        }
};

#endif
