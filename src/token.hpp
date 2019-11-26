#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token {

    public:
        enum Kind {
            // Keywords
            Let,
            Mut,
            Print,

            // Literals
            Identifier,
            Number,
            
            // Brackets
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
            
            // Special groups
            AmpersandMut,

            // Comments, EOF or Errors
            Comment,
            End,
            Unexpected,
        };

        Token(Kind kind, unsigned int line)
            : m_kind{kind}, m_line{line} {}

        Token(Kind kind, unsigned int line, std::string lexeme)
            : m_kind(kind), m_line(line), m_lexeme(lexeme) {}

        Token(Kind kind, unsigned int line, char c)
            : m_kind(kind), m_line(line), m_lexeme(std::string(1, c)) {}

        unsigned int on_line() { return m_line; }

        Kind kind() const { return m_kind; }

        void kind(Kind kind) { m_kind = kind; }

        bool is(Kind kind) const { return m_kind == kind; }

        bool is_not(Kind kind) const { return m_kind != kind; }

        bool is_one_of(Kind kind1, Kind kind2) const { return is(kind1) || is(kind2); }

        template <typename ...Ts>
        bool is_one_of(Kind kind1, Kind kind2, Ts... ks) const {
            return is(kind1) || is_one_of(kind2, ks...);
        }

        std::string lexeme() const {
            return m_lexeme;
        }

        void lexeme(std::string lex) {
            m_lexeme = lex;
        }

    private:
        unsigned int m_line;
        Kind m_kind;
        std::string m_lexeme;

};

#endif
