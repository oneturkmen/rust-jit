#include "ast_printer.hpp"

std::string visitExpr(Expr* expr) {
    return expr->accept(this);
}

std::string visitIdentifier(Identifier* id) {
    return id->m_token.lexeme();
}

std::string visitBinaryExpr() {
    
}

std::string visitUnaryExpr() {

}

std::string visitGroupingExpr() {

}
