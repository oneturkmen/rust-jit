#include "ast_printer.hpp"

std::string ASTPrinter::visitExprStmt(ExprStmt* exprStmt) {
    return exprStmt->accept(this);
}

std::string ASTPrinter::visitPrintStmt(PrintStmt* printStmt) {
    return printStmt->accept(this);
}

std::string ASTPrinter::visitExpr(Expr* expr) {
    return expr->accept(this);
}

std::string ASTPrinter::visitLiteral(Literal* id) {
    return id->m_token.lexeme();
}

std::string ASTPrinter::visitBinaryExpr(BinaryExpr* bin_expr) {
    return bin_expr->m_left->accept(this) 
        + bin_expr->m_op.lexeme() 
        + bin_expr->m_right->accept(this);
}

std::string ASTPrinter::visitUnaryExpr(UnaryExpr* unary_expr) {
    return unary_expr->m_op.lexeme() 
        + unary_expr->m_right->accept(this);
}

std::string ASTPrinter::visitGroupingExpr(GroupingExpr* grouping_expr) {
    return "(" + grouping_expr->m_expr->accept(this)  + ")";
}
