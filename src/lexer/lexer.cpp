#include "lexer.hpp"

#include <sstream>

// ------ Non-class functions -------

bool is_space(char c) {
    switch(c) {
        case ' ':
        case '\r':
        case '\t':
        case '\n':
            return true;
        default:
            return false;
    }
}

bool is_identifier_char(char c) {
    switch (c) {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '_':
            return true;
        default:
            return false;
    }
}

bool is_digit(char c) {
    switch (c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return true;
        default:
            return false;
    }
}

// -------------- END ---------------


Lexer::Lexer(const std::string& file_name) {
    // Read into buffer and store as a single string
    // inside the class.
    source.open(file_name);

    std::stringstream buffer;

    buffer << source.rdbuf();

    text = std::move(buffer.str());

    // Initialize pointer to currently processed character
    m_beg = text.c_str();
}

// Atomic lexemes
Token Lexer::atom(Token::Kind kind) {
    ++current;
    return Token(kind, m_line_lex, m_beg++, 1);
}

Token Lexer::identifier() {
    const char * start = m_beg;
    get();
    while (is_identifier_char(peek())) get();
    return Token(Token::Kind::Identifier, m_line_lex, start, m_beg);
}

Token Lexer::number() {
    const char * start = m_beg;
    get();
    while (is_digit(peek())) get();
    return Token(Token::Kind::Number, m_line_lex, start, m_beg);
}

Token Lexer::slash_or_comment() {
    const char * start = m_beg;
    get();
    if (peek() == '/') {
        // Comment
        get();
        start = m_beg;
        while (peek() != '\0') {
            if (get() == '\n') {
                return Token(Token::Kind::Comment, m_line_lex, start,
                        std::distance(start, m_beg) - 1); // ignore newline
            }
        }
    } else {
        // Division
        return Token(Token::Kind::Slash, m_line_lex, start, 1);
    }
}

Token Lexer::less_than_or_equal() {
    const char * start = m_beg;
    get();
    if (peek() == '=') {
        get(); // transition to next token
        return Token(Token::Kind::LessThanOrEqual, m_line_lex, start, 2);
    } else {
        return Token(Token::Kind::LessThan, m_line_lex, start, 1);
    }
}

Token Lexer::greater_than_or_equal() {
    const char * start = m_beg;
    get();
    if (peek() == '=') {
        get(); // transition to next token
        return Token(Token::Kind::GreaterThanOrEqual, m_line_lex, start, 2);
    } else {
        return Token(Token::Kind::GreaterThan, m_line_lex, start, 1);
    }
}

Token Lexer::equal() {
    const char * start = m_beg;
    get();
    if (peek() == '=') {
        get(); // transition to next token
        return Token(Token::Kind::DoubleEqual, m_line_lex, start, 2);
    } else {
        return Token(Token::Kind::Equal, m_line_lex, start, 1);
    }
}

Token Lexer::string() {
    const char * start = m_beg;
    get(); // consume LHS double quote
    while (peek() != '"' && !is_end()) {
        if (peek() == '\n') ++m_line_lex;
        get();
    }

    if (is_end()) {
        return Token(Token::Kind::Unexpected, m_line_lex);
    }

    get(); // consume RHS double quote

    return Token(Token::Kind::String, m_line_lex, start + 1, 
            std::distance(start, m_beg) - 2);
}

Token Lexer::next() {
    while (is_space(peek())) {
        if (peek() == '\n') m_line_lex++;
        get();
    }

    switch (peek()) {
        case '\0':
            return Token(Token::Kind::End, m_line_lex, m_beg, 1);
        default:
            return atom(Token::Kind::Unexpected);
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
            return identifier();
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return number();
        case '(':
            return atom(Token::Kind::LeftParen);
        case ')':
            return atom(Token::Kind::RightParen);
        case '{':
            return atom(Token::Kind::LeftCurly);
        case '}':
            return atom(Token::Kind::RightCurly);
        case '>':
            return greater_than_or_equal(); // handle non-strict inequality
        case '<':
            return less_than_or_equal();
        case '=':
            return equal(); // assignment or comparison
        case '+':
            return atom(Token::Kind::Plus);
        case '-':
            return atom(Token::Kind::Minus);
        case '*':
            return atom(Token::Kind::Asterisk);
        case '/':
            return slash_or_comment(); // whether division or comment
        case '&':
            return atom(Token::Kind::Ampersand);
        case ';':
            return atom(Token::Kind::Semicolon);
        case '"':
            return string();
    }
}
