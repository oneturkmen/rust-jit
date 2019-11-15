
#include "parser.hpp"

Expr* Parser::expression() {
    return equality();
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
        || match(Token::Kind::Minus)) {
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

    if (match(Token::Kind::LeftParen)) {
        Expr* expr = expression();

        if (!match(Token::Kind::RightParen)) {
            throw "Expected \")\" - did you miss it?";
            // TODO: error handling here pleeaseee
        }

        return new GroupingExpr(expr);
    }
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
