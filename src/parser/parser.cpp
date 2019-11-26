#include "parser.hpp"

std::vector<Stmt*> Parser::parse() {
    std::vector<Stmt*> stmts;

    while (!Parser::is_end()) {
        stmts.push_back(declaration());
    }

    return stmts;
}

Stmt* Parser::declaration() {
    if (match(Token::Kind::Let)) {
        return varDeclaration();
    }

    return statement();
}

Stmt* Parser::varDeclaration() {
    // If current token is "mut", then
    // variable is mutable. Apparently, it's also a C++ keyword.
    bool _mutable = match(Token::Kind::Mut);

    Token name = get();
    Expr* initializer = nullptr;

    if (!match(Token::Kind::Equal)) {
        std::cout << "Error: '=' expected after 'let'! Cannot infer type without it.\n";
        throw "Error: '=' expected after 'let'! Cannot infer type without it.\n";
    }

    initializer = expression();

    if (!match(Token::Kind::Semicolon)) {
        std::cout << "Error: ';' expected after expression!\n";
        throw "Expected ';' after expression!";
    }

    return new VarDeclStmt(name, initializer, _mutable);
}

Stmt* Parser::statement() {
    // All language-defined keywords are listed here
    if (match(Token::Kind::Print)) {
        return printStmt();
    }

    return exprStmt();
}

Stmt* Parser::exprStmt() {
    Expr* expr = expression();

    if (!match(Token::Kind::Semicolon)) {
        std::cout << "Error: ';' expected after expression!\n";
        throw "Expected ';' after expression!";
    }

    return new ExprStmt(expr);
}

Stmt* Parser::printStmt() {
    Expr* expr = expression();

    if (!match(Token::Kind::Semicolon)) {
        std::cout << "Error: ';' expected after expression!\n";
        throw "Expected ';' after expression!";
    }

    return new PrintStmt(expr);
}

Expr* Parser::expression() {
    return assignment();
}

Expr* Parser::assignment() {
     // Parse LHS if next token is "=".
     // This should be identifier if next token is "=".
     // Otherwise, it's treated as RHS (r-value).
    Expr* expr = equality();

    if (match(Token::Kind::Equal)) {
        Expr* value = assignment(); // parse RHS

        if (dynamic_cast<Identifier*>(expr)) {
            Token name = dynamic_cast<Identifier*>(expr)->m_token;
            return new AssignExpr(name, value);
        }

        std::cout << "ERROR: Invalid left-hand side assignment!\n";
    }

    return expr;
}

Expr* Parser::equality() {
    Expr* expr = comparison();

    // TODO: gotta include "!=" some time
    while (match(Token::Kind::DoubleEqual)) {
        //  Left-associative, i.e.,
        // ((expr, op_0, right_1), op_1, right_2) ...
        Token op = previous();
        Expr* right = comparison();
        expr = new BinaryExpr(expr, op, right);
    }

    return expr;
}

Expr* Parser::comparison() {
    Expr* expr = addition();

    while (match(Token::Kind::GreaterThanOrEqual)
            || match(Token::Kind::LessThanOrEqual)
            || match(Token::Kind::LessThan)
            || match(Token::Kind::GreaterThan)) {
        Token op = previous();
        Expr* right = addition();
        expr = new BinaryExpr(expr, op, right);
    }

    return expr;
}

Expr* Parser::addition() {
    Expr* expr = multiplication();

    while (match(Token::Kind::Plus) || match(Token::Kind::Minus)) {
        Token op = previous();
        Expr* right = multiplication();
        expr = new BinaryExpr(expr, op, right);
    }

    return expr;
}

Expr* Parser::multiplication() {
    Expr* expr = unary();

    while (match(Token::Kind::Asterisk) || match(Token::Kind::Slash)) {
        Token op = previous();
        Expr* right = unary();
        expr = new BinaryExpr(expr, op, right);
    }

    return expr;
}

Expr* Parser::unary() {
    if (match(Token::Kind::Ampersand)
        || match(Token::Kind::Asterisk)
        || match(Token::Kind::Minus)
        || match(Token::Kind::AmpersandMut)) {
        Token op = previous();
        Expr* right = unary();
        return new UnaryExpr(op, right);
    }

    return primary();
}

Expr* Parser::primary() {
    // Keywords
    if (match(Token::Kind::Number) || match(Token::Kind::String)) {
        return new Literal(previous());
    }

    // Identifier corresponds to a variable
    if (match(Token::Kind::Identifier)) {
        return new Identifier(previous());
    }

    if (match(Token::Kind::LeftParen)) {
        Expr* expr = expression();

        if (!match(Token::Kind::RightParen)) {
            throw "Expected \")\" - did you miss it?";
            // TODO: error handling here pleeaseee
        }

        return new GroupingExpr(expr);
    }

    return nullptr;
}

Token Parser::previous() {
    return (current == 0)
        ? m_tokens[current]
        : m_tokens[current - 1];
}

Token Parser::peek() {
    return m_tokens[current];
}

Token Parser::get() {
    if (is_end()) {
        return previous();
    }

    // Consume and shift to the next token
    return m_tokens[current++];
}

bool Parser::is_end() {
    return current >= m_tokens.size()
        || m_tokens[current].is(Token::Kind::End);
}

bool Parser::check(Token::Kind kind) {
    if (is_end()) {
        return false;
    }

    return peek().is(kind);
}

bool Parser::match(Token::Kind kind) {
    if (check(kind)) {
        get(); // advance to next if token type matches
        return true;
    }

    return false;
}
