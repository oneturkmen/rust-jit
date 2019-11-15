
#include <iomanip>
#include <iostream>
#include <vector>

#include "lexer.hpp"
#include "parser.hpp"


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


    return 0;
}
