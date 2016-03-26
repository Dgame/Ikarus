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

void AbstractLexer::parseString() {
    this->expect('"');

    std::string str;
    str.reserve(8);
    while (this->isValid() && !this->accept('"')) {
        str += *_ptr;
        _ptr++;
    }

    _token->setString(str);
}

void AbstractLexer::parseIdentifier() {
    std::string str;
    str.reserve(8);

    if (!(std::isalpha(*_ptr) || *_ptr == '_')) {
        error("Invalid identifier");
    }

    while (this->isValid() && (std::isalnum(*_ptr) || *_ptr == '_')) {
        str += *_ptr;

        _ptr++;
    }

    _token->setIdentifier(str);
}

void AbstractLexer::parseNumeric() {
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

        _token->setDecimal(value + (dec / pot));

        debug("Found decimal ", _token->getDecimal());
    } else {
        _token->setInteger(value);

        debug("Found integer ", _token->getInteger());
    }
}

AbstractLexer::AbstractLexer(const char* pos, const char* const end) : _ptr(pos), _end(end), _token(new Token()) { }

Token* AbstractLexer::peek(Token* tok) {
    Token* result = nullptr;
    if (tok->next) {
        result = tok->next.get();
    } else {
        result = new Token();
        this->scan(result);
        tok->next.reset(result);
    }

    return result;
}

Token::Type AbstractLexer::peekNext() {
    Token* tok = this->getToken();
    return this->peek(tok)->getType();
}

Token::Type AbstractLexer::peekNext2() {
    Token* tok = this->getToken();
    tok = this->peek(tok);

    return this->peek(tok)->getType();
}

Token::Type AbstractLexer::next() {
    if (_token->next) {
        _token.swap(_token->next);
    } else {
        Token* tok = this->getToken();
        this->scan(tok);
    }

    return _token->getType();
}

bool AbstractLexer::accept(Token::Type type) {
    if (this->getToken()->is(type)) {
        this->next();

        return true;
    }

    return false;
}

void AbstractLexer::expect(Token::Type type) {
    if (!this->accept(type)) {
        error("Unexpected Token '", this->getToken()->asString(), "'. Expected '", Token::AsString(type), "'");
    }
}