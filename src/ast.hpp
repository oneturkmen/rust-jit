#ifndef AST_H
#define AST_H

#include <string>

#include "token.hpp"
#include "ast_visitor.hpp"

/**
 * Base class for all expressions.
 */
class Expr {
    public:
        virtual std::string accept(Visitor<std::string>* visitor) = 0;
};


/**
 * Identifier is an expression.
 */
class Identifier: public Expr {
    public:
        Identifier(Token token)
            : m_token{token} { }

        std::string accept(Visitor<std::string>* visitor) {
            return visitor->visitIdentifier(this);
        }

        // Fields
        Token m_token;
};

/**
 * Binary expression.
 */
class BinaryExpr: public Expr {
    public:
        BinaryExpr(Expr* left, Token op, Expr* right)
            : m_left{left}, m_op{op}, m_right{right} { }

    private:
        Expr* m_left;
        Token m_op;
        Expr* m_right;
};


/**
 * Unary expression.
 */
class UnaryExpr: public Expr {
    public:
        UnaryExpr(Token op, Expr* right)
            : m_op{op}, m_right{right} { }

    private:
        Token m_op;
        Expr* m_right;
};


/**
 * Expression inside parenthesis.
 */
class GroupingExpr: public Expr {
    public:
        GroupingExpr(Expr* expr)
            : m_expr{expr} { }

    private:
        Expr* m_expr;
};

#endif
