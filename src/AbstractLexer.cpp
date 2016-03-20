#include "AbstractLexer.hpp"
#include "util.hpp"

void AbstractLexer::skipSpaces() {
    while (std::isspace(*_ptr)) {
        _ptr++;
    }
}

bool AbstractLexer::accept(char c) {
    this->skipSpaces();

    if (*_ptr == c) {
        _ptr++;

        return true;
    }

    return false;
}

void AbstractLexer::expect(char c) {
    if (!this->accept(c)) {
        error("Expected ", c, " not found");
    }
}

bool AbstractLexer::isValid() const {
    return _ptr <= _end && *_ptr != '\0';
}

void AbstractLexer::parsePrefix() {
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

void AbstractLexer::parseString(Token& token) {
    this->expect('"');

    std::string str;
    str.reserve(8);
    while (this->isValid() && !this->accept('"')) {
        str += *_ptr;
        _ptr++;
    }

    token.setString(str);
}

void AbstractLexer::parseIdentifier(Token& token) {
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

void AbstractLexer::parseNumeric(Token& token) {
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

AbstractLexer::AbstractLexer(const char* pos, const char* const end) : _ptr(pos), _end(end) { }

const Token* AbstractLexer::getToken() const {
    static Token Invalid;

    if (_index >= _token.size()) {
        return &Invalid;
    }

    return &_token.at(_index);
}

const Token* AbstractLexer::nextToken() {
    if (_index < _token.size()) {
        _index++;
    }

    return this->getToken();
}

const Token* AbstractLexer::accept(Token::Type type) {
    const Token* tok = this->getToken();
    if (tok->is(type)) {
        this->nextToken();

        return tok;
    }

    return nullptr;
}

void AbstractLexer::expect(Token::Type type) {
    if (!this->accept(type)) {
        error("Unexpected Token");
    }
}