#include "jit.hpp"

/**
 * Just-in-time compilation with Eclipse OMR.
 */

void compile(std::vector<Stmt*> stmts) {
    std::cout << "# of stmts: " << stmts.size() << std::endl;
    for (auto stmt : stmts) {
        execute(stmt);
    }

    // 1. Generate OMR IR through JitBuilder. Helper class will help :D
    // 2. Compile via JitBuilder.
    // 3. Call that via JitBuilder.
}



OMR::JitBuilder::IlValue* visitVarDeclStmt(VarDeclStmt* varDeclStmt) {

}

OMR::JitBuilder::IlValue* visitExprStmt(ExprStmt* exprStmt) {

}

OMR::JitBuilder::IlValue* visitPrintStmt(PrintStmt* printStmt) {

}

OMR::JitBuilder::IlValue* visitExpr(Expr* expr) {
    std::cout << "Jit::visitExpr()\n";

    return evaluate(expr);
}

OMR::JitBuilder::IlValue* visitAssignExpr(AssignExpr* assign_expr) {

}

OMR::JitBuilder::IlValue* visitIdentifier(Identifier* identifier) {
    std::cout << "Jit::visitIdentifier()\n";

    Token token = identifier->m_token;

    return il->Load(token.lexeme());
}

OMR::JitBuilder::IlValue* visitLiteral(Literal* literal) {
    std::cout << "Jit::visitLiteral()\n";

    Token curr_token = literal->m_tokenc;

    if (curr_token.is(Token::Kind::Number)) {
        return il->Const(std::stoi(curr_token.lexeme()));
    }
    else if (curr_token.is(Token::Kind::String)) {
        return il->ConstString(curr_token.lexeme());
    }
    else {
        throw "Literal type not recognized";
    }
}

OMR::JitBuilder::IlValue* visitBinaryExpr(BinaryExpr* bin_expr) {
    std::cout << "Jit::visitBinaryExpr\n";

    OMR::JitBuilder::IlValue* left = evaluate(bin_expr->m_left);
    OMR::JitBuilder::IlValue* right = evaluate(bin_expr->m_right);

    switch (bin_expr->m_op.kind()) {
        // Arithmetic
        case Token::Kind::Minus:
            return il->Sub(left, right);
        case Token::Kind::Plus:
            return il->Add(left, right);
        case Token::Kind::Slash:
            return il->Div(left, right);
        case Token::Kind::Asterisk:
            return il->Mul(left, right);

        // Comparison
        case Token::Kind::GreaterThan:
            // TODO should be boolean
            return il->GreaterThan(left, right);
        case Token::Kind::LessThan:
            return il->LessThan(left, right);
        case Token::Kind::GreaterThanOrEqual:
            return il->GreaterOrEqualTo(left, right);
        case Token::Kind::LessThanOrEqual:
            return il->LessOrEqualTo(left, right);
        case Token::Kind::DoubleEqual:
            return il->EqualTo(left, right);
    }

    return nullptr;
}

OMR::JitBuilder::IlValue* visitUnaryExpr(UnaryExpr* unary_expr) {
    std::cout << "Jit::visitUnaryExpr()\n";

    OMR::JitBuilder::IlValue* right = evaluate(unary_expr->m_right);

    switch (unary_expr->m_op.kind()) {
        case Token::Kind::Minus: // TODO validation of types
            return il->Sub(ConstInt32(0), right);
        case Token::Kind::Ampersand: {
            Identifier* identifier = dynamic_cast<Identifier*>(unary_expr->m_right);
            if (identifier) {
                // TODO: Set some boolean is_reference to check in assignExpr/VarDecl
                // so that we know if reference is coming or not
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

OMR::JitBuilder::IlValue* visitGroupingExpr(GroupingExpr* group_expr) {
    std::cout << "Jit::visitGroupingExpr()\n";
    return evaluate(group_expr->m_expr);
}
