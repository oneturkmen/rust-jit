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
        virtual std::string accept(ASTVisitor<std::string>* visitor) = 0;
};


/**
 * Literal is an expression.
 */
class Literal: public Expr {
    public:
        Literal(Token token)
            : m_token{token} { }

        std::string accept(ASTVisitor<std::string>* visitor) {
            return visitor->visitLiteral(this);
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

        std::string accept(ASTVisitor<std::string>* visitor) {
            return visitor->visitBinaryExpr(this);
        }

        // Fields
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

        std::string accept(ASTVisitor<std::string>* visitor) {
            return visitor->visitUnaryExpr(this);
        }

        // Fields
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

        std::string accept(ASTVisitor<std::string>* visitor) {
            return visitor->visitGroupingExpr(this);
        }

        // Fields
        Expr* m_expr;
};

#endif
