#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "ast.hpp"
#include "token.hpp"

class Parser {

    public:
        Parser(std::vector<Token> tokens)
            : m_tokens{tokens} { }

        // TODO: Include error handling (exceptions for panic mode + sync)
        std::vector<Stmt*> parse();

    // Rules
    private:
        Stmt* declaration();
        Stmt* varDeclaration();
        Stmt* statement();
        Stmt* exprStmt();
        Stmt* printStmt();
        Expr* expression();
        Expr* assignment();
        Expr* equality();
        Expr* comparison();
        Expr* addition();
        Expr* multiplication();
        Expr* unary();
        Expr* primary();


        // Helpers
        Token previous();
        Token peek();
        Token get();

        bool is_end();
        bool check(Token::Kind kind);
        bool match(Token::Kind kind);

    // Fields
    private:
        const std::vector<Token> m_tokens;
        unsigned int current = 0;
};

#endif
