#ifndef AST_VISITOR_H
#define AST_VISITOR_H


// Forward declaration of all classes to be visited
class Expr;
class Identifier;
class BinaryExpr;
class UnaryExpr;
class GroupingExpr;


/**
 * Base class for any visitor subclass. All
 * methods here are abstract.
 */
template <class T>
class ASTVisitor {
    public:
        virtual T visitExpr(Expr* expr) = 0;
        virtual T visitIdentifier(Identifier* id) = 0;
        virtual T visitBinaryExpr(BinaryExpr* bin_expr) = 0;
        virtual T visitUnaryExpr(UnaryExpr* unary_expr) = 0;
        virtual T visitGroupingExpr(GroupingExpr* group_expr) = 0;
};

#endif

