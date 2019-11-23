
#include <iomanip>
#include <iostream>
#include <vector>

#include "ast_printer.hpp"
#include "interpreter.hpp"
#include "lexer.hpp"
#include "parser.hpp"

std::ostream& operator<<(std::ostream& os, const Token::Kind& kind) {
    static const char * const names[]{
            "Let",
            "Mut",
            "Print",
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

    Interpreter interpreter;

    std::string source;

    while (true) {
        // std::string name = "ex1.rs";
        std::cout << "> ";
        std::getline(std::cin, source);

        if (source == "q") break;

        Lexer lexis(source);

        std::vector<Token> tokens;
        for (auto token = lexis.next(); 
                not token.is_one_of(Token::Kind::End, Token::Kind::Unexpected); 
                token = lexis.next()) {

            std::cout << std::setw(12) << token.kind() << " | " << token.lexeme() << " | " << token.on_line() << " | \n";

            tokens.push_back(token);
        }

        // Parse into a tree
        Parser parser(tokens);
        std::vector<Stmt*> parse_tree = parser.parse();

        // Print the contents
        //ASTPrinter printer;
        //std::cout << "AST Printer >>>> " << printer.print(parse_tree) << "\n";

        // Evaluate
        interpreter.interpret(parse_tree);
    }

    return 0;
}
