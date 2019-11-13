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

class Token {

    public:
        enum Kind {
            // Literals
            Identifier,
            Number,

            LeftParen,
            RightParen,
            LeftCurly,
            RightCurly,

            // Comparison
            LessThan,
            GreaterThan,
            LessThanOrEqual,
            GreaterThanOrEqual,
            DoubleEqual,

            // Assignment
            Equal,

            // Arithmetic
            Plus,
            Minus,
            Asterisk,
            Slash,

            // Single character
            Ampersand,
            Semicolon,
            String,

            // Comments, EOF or Errors
            Comment,
            End,
            Unexpected,
        };

        Token(Kind kind, unsigned int line)
            : m_kind{kind}, m_line{line} {}

        Token(Kind kind, unsigned int line, const char* beg, size_t len)
            : m_kind(kind), m_line(line), m_lexeme(beg, len) {}

        Token(Kind kind, unsigned int line, const char* beg, const char* end)
            : m_kind(kind), m_line(line), m_lexeme(beg, std::distance(beg, end)) {}

        unsigned int on_line() { return m_line; }

        Kind kind() const { return m_kind; }

        void kind(Kind kind) { m_kind = kind; }

        bool is(Kind kind) { return m_kind == kind; }

        bool is_not(Kind kind) { return m_kind != kind; }

        bool is_one_of(Kind kind1, Kind kind2) { return is(kind1) || is(kind2); }

        template <typename ...Ts>
        bool is_one_of(Kind kind1, Kind kind2, Ts... ks) {
            return is(kind1) || is_one_of(kind2, ks...);
        }

        std::string_view lexeme() const {
            return m_lexeme;
        }

        void lexeme(std::string_view lex) {
            m_lexeme = std::move(lex);
        }

    private:

        unsigned int m_line;
        Kind m_kind;
        std::string_view m_lexeme;
};

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

        char peek() { return *m_beg; }
        char get() {
            ++current;
            return *m_beg++;
        }

        bool is_end() { return current >= text.length() || peek() == '\0'; }

    private:

        std::string text;

        const char * m_beg = nullptr;
        unsigned int m_line_lex = 1;
        unsigned int current = 0;

        std::ifstream source;
};

#endif
