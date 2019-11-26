
#include <iomanip>
#include <iostream>
#include <vector>

#include "ast/ast_printer.hpp"
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
            "AmpersandMut",
            "Comment",
            "End",
            "Unexpected",
    };
    return os << names[static_cast<int>(kind)];
}

/**
 * Starts interactive shell.
 */
void run_repl() {
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
}


/**
 * Read and interpret the file instead.
 */
void run_source(char* file_name) {
    std::cout << "Running source ...\n";
    Interpreter interpreter;

    Lexer lexis;
    lexis.read_file(file_name);

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

    // Evaluate
    interpreter.interpret(parse_tree);
}


int main(int argc, char* argv[]) {

    if (argc == 2) {
        run_source(argv[1]);
    } 
    else if (argc == 1) {
        run_repl();
    }
    else {
        std::cout << "Rust-jit\n";
        std::cout << "Experimental work to dynamically compile Rust lang. \n";
        std::cout << "It's currently work-in-progress and works on a very minimal\n";
        std::cout << "subset of the language.\n";
        std::cout << "\n";
        std::cout << "./lexer [FILE]\n";
        std::cout << "\n";
        std::cout << "If FILE is not provided, then starts command-line interpreter.\n";
        std::cout << "Otherwise, reads and interprets the source\n";
        std::cout << "CMPUT 500, oneturkmen, 2019\n\n";
    }

    

    return 0;
}
