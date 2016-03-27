#include "AbstractLexer.hpp"
#include "util.hpp"

void AbstractLexer::skipSpaces() {
    while (_location.isSpace()) {
        _location.next();
    }
}

bool AbstractLexer::accept(char c) {
    this->skipSpaces();

    if (_location.is(c)) {
        _location.next();

        return true;
    }

    return false;
}

void AbstractLexer::expect(char c) {
    if (!this->accept(c)) {
        error("Expected ", c, " not found @ ", _location.getLine());
    }
}

void AbstractLexer::parseString() {
    this->expect('"');

    std::string str;
    str.reserve(8);
    while (_location.isValid() && !this->accept('"')) {
        str += _location.get();
        _location.next();
    }

    _token->setString(str);
}

void AbstractLexer::parseIdentifier() {
    std::string str;
    str.reserve(8);

    if (!_location.isAlpha() && !_location.is('_')) {
        error("Invalid identifier @ ", _location.getLine());
    }

    while (_location.isValid() && (_location.isAlphaNumeric() || _location.is('_'))) {
        str += _location.get();
        _location.next();
    }

    _token->setIdentifier(str);
}

void AbstractLexer::parseNumeric() {
    enforce(_location.isDigit(), "Expected number @ ", _location.getLine());

    i32_t value = 0;
    while (_location.isDigit()) {
        const char c = _location.get();

        value *= 10;
        value += static_cast<i32_t>(c - '0');

        _location.next();
    }

    if (this->accept('.')) {
        f32_t pot = 1;
        f32_t dec = 0;

        while (_location.isDigit()) {
            const char c = _location.get();

            pot *= 10;
            dec *= 10;
            dec += static_cast<i32_t>(c - '0');

            _location.next();
        }

        _token->setDecimal(value + (dec / pot));

        debug("Found decimal ", _token->getDecimal());
    } else {
        _token->setInteger(value);

        debug("Found integer ", _token->getInteger());
    }
}

AbstractLexer::AbstractLexer(const char* pos, const char* const end) : _location(pos, end), _token(new Token()) { }

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
        error("Unexpected Token '", this->getToken()->asString(), "'. Expected '", Token::AsString(type), "' @ ", _location.getLine());
    }
}