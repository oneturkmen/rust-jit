#ifndef TOKEN_H
#define TOKEN_H

#include <string>

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

#endif
