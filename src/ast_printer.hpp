#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include <string>

#include "ast_visitor.hpp"
#include "ast.hpp"


class ASTPrinter: ASTVisitor<std::string> {
    public:
        std::string visitExpr(Expr* expr);
        std::string visitIdentifier(Identifier* id);
        std::string visitBinaryExpr(BinaryExpr* bin_expr);
        std::string visitUnaryExpr(UnaryExpr* unary_expr);
        std::string visitGroupingExpr(GroupingExpr* group_expr);
};

#endif
