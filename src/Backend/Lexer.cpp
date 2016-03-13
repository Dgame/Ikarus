#include "Lexer.hpp"

#include <locale>
#include "Token.hpp"
#include "util.hpp"

void Lexer::skipSpaces() {
    while (std::isspace(*_ptr)) {
        _ptr++;
    }
}

bool Lexer::accept(char c) {
    this->skipSpaces();

    if (*_ptr == c) {
        _ptr++;

        return true;
    }

    return false;
}

void Lexer::expect(char c) {
    if (!this->accept(c)) {
        error("Expected ", c, " not found");
    }
}

bool Lexer::isValid() const {
    return _ptr <= _end;
}

void Lexer::parsePrefix() {
    bool op_not = false;
    bool op_neg = false;

    while (this->isValid()) {
        if (this->accept('!')) {
            op_not = !op_not;
        } else if (this->accept('-')) {
            op_neg = !op_neg;
        } else {
            break;
        }
    }

    if (op_not) {
        _token.push_back(Token(Token::NOT));
    }

    if (op_not) {
        _token.push_back(Token(Token::NEGATE));
    }
}

void Lexer::parseString(Token& token) {
   this->expect('"');

    std::string str;
    str.reserve(8);
    while (this->isValid() && !this->accept('"')) {
        str += *_ptr;

        _ptr++;
    }

    token.setString(str);
}

void Lexer::parseIdentifier(Token& token) {
    std::string str;
    str.reserve(8);

    if (!(std::isalpha(*_ptr) || *_ptr == '_')) {
        error("Invalid identifier");
    }

    while (this->isValid() && (std::isalnum(*_ptr) || *_ptr == '_')) {
        str += *_ptr;

        _ptr++;
    }

    token.setIdentifier(str);
}

void Lexer::parseNumeric(Token& token) {
    this->parsePrefix();
    this->skipSpaces();

    enforce(std::isdigit(*_ptr), "Expected number");

    i32_t value = 0;
    while (isdigit(*_ptr)) {
        value *= 10;
        value += static_cast<i32_t>(*_ptr - '0');

        _ptr++;
    }

    if (this->accept('.')) {
        f32_t pot = 1;
        f32_t dec = 0;

        while (isdigit(*_ptr)) {
            pot *= 10;
            dec *= 10;
            dec += static_cast<i32_t>(*_ptr - '0');

            _ptr++;
        }

        token.setDecimal(value + (dec / pot));

        debug("Found decimal ", token.getDecimal());
    } else {
        token.setInteger(value);

        debug("Found integer ", token.getInteger());
    }
}

bool Lexer::parse(Token& token) {
    this->skipSpaces();

    if (this->accept('~')) {
        debug("found offset");

        token.setType(Token::TILDE);
    } else if (this->accept('&')) {
        debug("found variable");

        token.setType(Token::AMPERSAND);
    } else if (this->accept('.')) {
        token.setType(Token::DOT);
    } else if (this->accept(',')) {
        token.setType(Token::COMMA);
    } else if (*_ptr == '"') {
        this->parseString(token);
    } else if (std::isalpha(*_ptr)) {
        this->parseIdentifier(token);
    } else if (std::isdigit(*_ptr)) {
        debug("found numeric");

        this->parseNumeric(token);
    } else {
        error("Unexpected Token ", *_ptr);
    }

    return token.getType() != Token::NONE;
}

Lexer::Lexer(const std::string& str) : _ptr(&str.front()), _end(&str.back()) {
    debug("---- LEXER START ----");

    while (this->isValid()) {
        Token token;
        if (this->parse(token)) {
            _token.push_back(token);
        }
    }

    debug("---- LEXER FINISHED ----");
}

const Token* Lexer::getNext() {
    static Token Invalid(Token::NONE);

    if (_index >= _token.size()) {
        return &Invalid;
    }

    return &_token.at(_index++);
}