#ifndef AST_H
#define AST_H

#include <iostream> // TODO: for debugging; should be removed
#include <string>

#include "token.hpp"
#include "ast_visitor.hpp"
#include "object.hpp"


/**
 * Base class for all types of statements.
 */
class Stmt {
    public:
        virtual std::string accept(ASTVisitor<std::string>* visitor) = 0;
        virtual Object* accept(ASTVisitor<Object*>* visitor) = 0;
};


/**
 * Class for variable declaration.
 */
class VarDeclStmt: public Stmt {
    public:
        VarDeclStmt(Token name, Expr* initializer)
            : m_name{name}, m_initializer{initializer} { }

        // For AST printer
        std::string accept(ASTVisitor<std::string>* visitor) {
            return visitor->visitVarDeclStmt(this);
        }

        // For Interpreter
        Object* accept(ASTVisitor<Object*>* visitor) {
            return visitor->visitVarDeclStmt(this);
        }

        Token m_name;
        Expr* m_initializer;
};


/**
 * Class for expression statement (one with ';').
 */
class ExprStmt: public Stmt {
    public:
        ExprStmt(Expr* expr)
            : m_expr{expr} { }

        // For AST printer
        std::string accept(ASTVisitor<std::string>* visitor) {
            return visitor->visitExprStmt(this);
        }

        // For Interpreter
        Object* accept(ASTVisitor<Object*>* visitor) {
            return visitor->visitExprStmt(this);
        }

        Expr* m_expr;
};


/**
 * Class for print statement.
 */
class PrintStmt: public Stmt {
    public:
        PrintStmt(Expr* expr)
            : m_expr{expr} { }

        // For AST printer
        std::string accept(ASTVisitor<std::string>* visitor) {
            return visitor->visitPrintStmt(this);
        }

        // For Interpreter
        Object* accept(ASTVisitor<Object*>* visitor) {
            return visitor->visitPrintStmt(this);
        }

        Expr* m_expr;
};


/**
 * Base class for all expressions.
 */
class Expr {
    public:
        virtual std::string accept(ASTVisitor<std::string>* visitor) = 0;
        virtual Object* accept(ASTVisitor<Object*>* visitor) = 0;
};


/**
 * Literal is an expression.
 */
class Literal: public Expr {
    public:
        Literal(Token token)
            : m_token{token} { }

        // For AST printer
        std::string accept(ASTVisitor<std::string>* visitor) {
            return visitor->visitLiteral(this);
        }

        // For Interpreter
        Object* accept(ASTVisitor<Object*>* visitor) {
            std::cout << "In Literal::accept(Object *)\n";
            return visitor->visitLiteral(this);
        }

        // Fields
        Token m_token;
};


/**
 * Identifier (for some variable).
 */
class Identifier: public Expr {
    public:
        Identifier(Token token)
            : m_token{token} { }

        // For AST printer
        std::string accept(ASTVisitor<std::string>* visitor) {
            return visitor->visitIdentifier(this);
        }

        // For Interpreter
        Object* accept(ASTVisitor<Object*>* visitor) {
            std::cout << "In Identifier::accept(Object *)\n";
            return visitor->visitIdentifier(this);
        }

        Token m_token;
};


/**
 * Assignment is an expression, which bugs my mind.
 * I guess you can treat is a mathematical operation with
 * "=" as an operator and two operands (l-value and r-value).
 */
class AssignExpr: public Expr {
    public:
        AssignExpr(Token token, Expr* expr)
            : m_token{token}, m_expr{expr} { }

        // For AST printer
        std::string accept(ASTVisitor<std::string>* visitor) {
            return visitor->visitAssignExpr(this);
        }

        // For Interpreter
        Object* accept(ASTVisitor<Object*>* visitor) {
            std::cout << "In AssignExpr::accept(Object *)\n";
            return visitor->visitAssignExpr(this);
        }

        Token m_token;
        Expr* m_expr;
};


/**
 * Binary expression.
 */
class BinaryExpr: public Expr {
    public:
        BinaryExpr(Expr* left, Token op, Expr* right)
            : m_left{left}, m_op{op}, m_right{right} { }

        // For AST printer
        std::string accept(ASTVisitor<std::string>* visitor) {
            return visitor->visitBinaryExpr(this);
        }

        // For Interpreter
        Object* accept(ASTVisitor<Object*>* visitor) {
            std::cout << "In BinExpr::accept(Object *)\n";
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

        // For AST printer
        std::string accept(ASTVisitor<std::string>* visitor) {
            return visitor->visitUnaryExpr(this);
        }

        // For Interpreter
        Object* accept(ASTVisitor<Object*>* visitor) {
            std::cout << "In UnaryExpr::accept(Object *)\n";
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

        // For AST printer
        std::string accept(ASTVisitor<std::string>* visitor) {
            return visitor->visitGroupingExpr(this);
        }

        // For Interpreter
        Object* accept(ASTVisitor<Object*>* visitor) {
            std::cout << "In GroupingExpr::accept(Object *)\n";
            return visitor->visitGroupingExpr(this);
        }

        // Fields
        Expr* m_expr;
};

#endif
