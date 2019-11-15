
#include <iomanip>
#include <iostream>
#include <vector>

#include "lexer.hpp"

// temporary
#include "ast.hpp"
#include "ast_printer.hpp"

std::ostream& operator<<(std::ostream& os, const Token::Kind& kind) {
    static const char * const names[]{
            "Identifier",
            "Number",
            "LeftParen",
            "RightParen",
            "LeftCurly",
            "RightCurly",
            "LessThan",
            "GreaterThan",
            "LessThanOrEqual",
            "GreaterThanOrEqual",
            "DoubleEqual",
            "Equal",
            "Plus",
            "Minus",
            "Asterisk",
            "Slash",
            "Ampersand",
            "Semicolon",
            "String",
            "Comment",
            "End",
            "Unexpected",
    };
    return os << names[static_cast<int>(kind)];
}

int main() {
    std::string name = "ex1.rs";
    
    Lexer lexis(name);

    std::vector<Token> tokens;
    for (auto token = lexis.next(); 
            not token.is_one_of(Token::Kind::End, Token::Kind::Unexpected); 
            token = lexis.next()) {

        std::cout << std::setw(12) << token.kind() << " | " << token.lexeme() << " | " << token.on_line() << " | \n";

        tokens.push_back(token);
    }

    Expr* expr = new BinaryExpr(
        new UnaryExpr(Token(Token::Kind::Asterisk, 1, "*"),
            new Literal(Token(Token::Kind::Identifier, 1, "foo"))),
        Token(Token::Kind::Plus, 1, "+"),
        new GroupingExpr(
            new BinaryExpr(
                new Literal(Token(Token::Kind::Number, 1, "123")),
                Token(Token::Kind::Slash, 1, "/"),
                new Literal(Token(Token::Kind::Number, 1, "420"))
            )
        )
    );

    ASTPrinter ast_printer;
    std::cout << ast_printer.print(expr) << std::endl;

    return 0;
}
