#include "interpreter.hpp"

void Interpreter::interpret(Expr* expr) {
    Object* obj = evaluate(expr);
    std::cout << obj->value() << "\n";
}

Object* Interpreter::visitLiteral(Literal* literal) {
    std::cout << "visitUnaryExpr()\n";
    Token curr_token = literal->m_token;

    if (curr_token.is(Token::Kind::Number)) {
        return new Number(std::stoi(curr_token.lexeme()));
    } 
    else if (curr_token.is(Token::Kind::String)) {
        return new String(curr_token.lexeme());
    }
    else {
        throw "Literal type not recognized";
    }
}

Object* Interpreter::visitExpr(Expr* expr) {
    std::cout << "visitExpr()\n";
    return evaluate(expr);
}

Object* Interpreter::visitUnaryExpr(UnaryExpr* unary_expr) {
    std::cout << "visitUnaryExpr()\n";
    Object* right = evaluate(unary_expr->m_right);

    switch (unary_expr->m_op.kind()) {
        case Token::Kind::Minus: // TODO validation of types
            return new Number(-std::stoi(right->value()));
        // TODO
        // case "*":
        // case "&"
    }

    return nullptr; // unreachable
}

Object* Interpreter::visitBinaryExpr(BinaryExpr* bin_expr) {
    Object* left = evaluate(bin_expr->m_left);
    Object* right = evaluate(bin_expr->m_right);

    switch (bin_expr->m_op.kind()) {
        // Arithmetic
        case Token::Kind::Minus:
            return new Number(std::stoi(left->value()) - std::stoi(right->value()));
        case Token::Kind::Plus: {
            if (left->type == Object::Type::NUMBER 
                && right->type == Object::Type::NUMBER) {
                // TODO: this is ugly - too many type conversions. Find a better way.
                return new Number(std::stoi(left->value()) + std::stoi(right->value()));
            }
            else if (left->type == Object::Type::STRING
                && right->type == Object::Type::STRING) {
                return new String(left->value() + right->value());
            }
        }
        case Token::Kind::Slash:
            return new Number(std::stoi(left->value()) / std::stoi(right->value()));
        case Token::Kind::Asterisk:
            return new Number(std::stoi(left->value()) * std::stoi(right->value()));

        // Comparison
        case Token::Kind::GreaterThan:
            // TODO should be boolean
            return new Number(
                (int) (std::stoi(left->value()) > std::stoi(right->value()))
            );
        case Token::Kind::LessThan:
            return new Number(
                (int) (std::stoi(left->value()) < std::stoi(right->value()))
            );
        case Token::Kind::GreaterThanOrEqual:
            return new Number(
                (int) (std::stoi(left->value()) >= std::stoi(right->value()))
            );
        case Token::Kind::LessThanOrEqual:
            return new Number(
                (int) (std::stoi(left->value()) <= std::stoi(right->value()))
            );
        case Token::Kind::DoubleEqual:
            return new Number(
                (int) (std::stoi(left->value()) == std::stoi(right->value()))
            );
    }
}

Object* Interpreter::visitGroupingExpr(GroupingExpr* group_expr) {
    return evaluate(group_expr->m_expr); // evaluate inner expression
}
