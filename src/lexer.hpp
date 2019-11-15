/*
 * Most of the work done by: J. Arrieta, Nabla Zero Labs, 2018.
 *
 * Modified to suit needs for lexical analysis for a minimal
 * subset of Rust lang.
 *
 * Adopted by: oneturkmen, 2019
 */


#ifndef LEXER_H
#define LEXER_H

#include <fstream>
#include <string>
#include <vector>

#include "token.hpp"

class Lexer {

    public:

        Lexer(const std::string& file_name);

        Token next();

    private:

        Token atom(Token::Kind kind);
        Token identifier();
        Token number();
        Token string();
        Token slash_or_comment();
        Token less_than_or_equal();
        Token greater_than_or_equal();
        Token equal();

        char peek() { return text[current]; }
        char get() {
            return text[current++];
        }

        bool is_end() { return current >= text.length() || peek() == '\0'; }

    private:

        std::string text;

        unsigned int m_line_lex = 1;
        unsigned int current = 0;

        std::ifstream source;
};

#endif
