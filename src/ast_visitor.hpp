#ifndef AST_VISITOR_H
#define AST_VISITOR_H


// Forward declaration of all classes to be visited
class VarDeclStmt;
class ExprStmt;
class PrintStmt;
class Expr;
class AssignExpr;
class Identifier;
class Literal;
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
        virtual T visitVarDeclStmt(VarDeclStmt* varDeclStmt) = 0;
        virtual T visitExprStmt(ExprStmt* exprStmt) = 0;
        virtual T visitPrintStmt(PrintStmt* printStmt) = 0;
        virtual T visitExpr(Expr* expr) = 0;
        virtual T visitAssignExpr(AssignExpr* assign_expr) = 0;
        virtual T visitIdentifier(Identifier* identifier) = 0;
        virtual T visitLiteral(Literal* literal) = 0;
        virtual T visitBinaryExpr(BinaryExpr* bin_expr) = 0;
        virtual T visitUnaryExpr(UnaryExpr* unary_expr) = 0;
        virtual T visitGroupingExpr(GroupingExpr* group_expr) = 0;
};

#endif

