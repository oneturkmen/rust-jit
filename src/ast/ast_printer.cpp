#include "ast_printer.hpp"

std::string ASTPrinter::visitVarDeclStmt(VarDeclStmt *varDeclStmt) {
    return varDeclStmt->m_name.lexeme()
        + " = "
        + varDeclStmt->m_initializer->accept(this);
}

std::string ASTPrinter::visitExprStmt(ExprStmt* exprStmt) {
    return exprStmt->m_expr->accept(this);
}

// FIXME: arguments naming convention is inconsistent. 
// Should either dead-snake or camel case, but not both.
std::string ASTPrinter::visitPrintStmt(PrintStmt* printStmt) {
    return printStmt->m_expr->accept(this);
}

std::string ASTPrinter::visitAssignExpr(AssignExpr* assign_expr) {
    return assign_expr->m_expr->accept(this);
}

std::string ASTPrinter::visitExpr(Expr* expr) {
    return expr->accept(this);
}

std::string ASTPrinter::visitLiteral(Literal* literal) {
    return literal->m_token.lexeme();
}

std::string ASTPrinter::visitIdentifier(Identifier* identifier) {
    return identifier->m_token.lexeme();
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
