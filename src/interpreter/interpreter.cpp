#include "interpreter.hpp"

void Interpreter::interpret(std::vector<Stmt*> stmts) {
    // std::cout << "# of stmts: " << stmts.size() << std::endl;
    for (auto stmt : stmts) {
        execute(stmt);
    }
}

// FIXME: make it more consistent
// Object* Interpreter::visitStmt(Stmt* statement) {
//     return evaluate(statement->accept(this));
// }

Object* Interpreter::visitVarDeclStmt(VarDeclStmt *varDeclStmt) {
    // std::cout << "visitVarDeclStmt()\n";
    Object* value = nullptr;

    if (varDeclStmt->m_initializer == nullptr) {
        std::cout << "Initializer expression for variable assigment is empty!\n";
        throw "Initializer expression for variable assigment is empty!\n";
    }

    // Evaluate
    value = evaluate(varDeclStmt->m_initializer);

    // Store in the environment
    std::string var_name = varDeclStmt->m_name.lexeme();
    bool is_mutable = varDeclStmt->m_mutable;

    Reference* ref = dynamic_cast<Reference*>(value);

    if (ref) {
        env.reference(var_name, ref->to, ref->_mutable);
    } 
    else if (value) {
        env.define(var_name, { is_mutable, false, false, value });
    }

    return value;
}

Object* Interpreter::visitExprStmt(ExprStmt* exprStmt) {
    // std::cout << "visitExprStmt()\n";
    return evaluate(exprStmt->m_expr);
}

Object* Interpreter::visitPrintStmt(PrintStmt* printStmt) {
    Object* result = evaluate(printStmt->m_expr);

    if (result == nullptr) return nullptr;

    // Print the result of evaluation
    result->print();

    return nullptr;
}

Object* Interpreter::visitAssignExpr(AssignExpr* assign_expr) {
    // std::cout << "visitAssignExpr()\n";
    Object* result = evaluate(assign_expr->m_expr);
    Reference* ref = dynamic_cast<Reference*>(result);

    if (ref) {
        env.reference(assign_expr->m_token.lexeme(), ref->to, ref->_mutable);
    } 
    else if (result) {
        env.assign(assign_expr->m_token.lexeme(), result);
    }

    return result;
}

Object* Interpreter::visitIdentifier(Identifier* identifier) {
    // std::cout << "visitIdentifier() <-> Variable Expression\n";
    Token token = identifier->m_token;

    return env.lookup(token.lexeme());
}

Object* Interpreter::visitLiteral(Literal* literal) {
    // std::cout << "visitLiteral()\n";
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
    // std::cout << "visitExpr()\n";
    return evaluate(expr);
}

Object* Interpreter::visitUnaryExpr(UnaryExpr* unary_expr) {
    // std::cout << "visitUnaryExpr()\n";
    Object* right = evaluate(unary_expr->m_right);

    switch (unary_expr->m_op.kind()) {
        case Token::Kind::Minus: // TODO validation of types
            return new Number(-std::stoi(right->value()));
        case Token::Kind::Ampersand: {
            Identifier* identifier = dynamic_cast<Identifier*>(unary_expr->m_right);
            if (identifier) {
                return new Reference(identifier->m_token.lexeme(), false);
            }
            std::cout << "ERROR: RHS is not an identifier!\n";
            return nullptr;
        }
        case Token::Kind::AmpersandMut: {
            Identifier* identifier = dynamic_cast<Identifier*>(unary_expr->m_right);
            if (identifier) {
                return new Reference(identifier->m_token.lexeme(), true);
            }
            std::cout << "ERROR: RHS is not an identifier!\n";
            return nullptr;
        }
        case Token::Kind::Asterisk: {
            // Dereferencing. RHS should be identifier of type Reference.

            // Cast right expression to an identifier.
            Identifier* identifier = dynamic_cast<Identifier*>(unary_expr->m_right);

            if (identifier) {
                // Dereference the Object value of the right expression. Uses extra point-to map.
                Object* value = env.dereference(identifier->m_token.lexeme());

                return value;
            }
        }
        // TODO
        // case "*":
        // case "&": address_of? or simple store in a map like points-to?
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
            else {
                std::cout << "Error: Mismatched types!\n";
                return nullptr;
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

    return nullptr;
}

Object* Interpreter::visitGroupingExpr(GroupingExpr* group_expr) {
    return evaluate(group_expr->m_expr); // evaluate inner expression
}
