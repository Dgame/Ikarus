//
// Created by Randy on 05.03.2016.
//

#include <locale>
#include <Lexer.hpp>
#include <util.hpp>
#include <NumericValue.hpp>

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

std::string Lexer::parseString() {
    this->skipSpaces();

    std::string value;
    value.reserve(8);
    while (std::isalpha(*_ptr) || *_ptr == '_') {
        value += *_ptr;
        _ptr++;
    }

    return value;
}

f32_t Lexer::parseNumber() {
    this->skipSpaces();

    const bool negate = this->accept('-');

    enforce(std::isdigit(*_ptr), "Expected number");

    f32_t value = 0;
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

        value += dec / pot;
    }

    return negate ? value * -1 : value;
}

Value* Lexer::parseValue() {
    if (std::isdigit(*_ptr) || *_ptr == '-')
        return new NumericValue(this->parseNumber());

    error("Unexpected Value ", *_ptr);

    return nullptr;
}

OpCode* Lexer::parseOpCode() {
    this->skipSpaces();

    if (this->accept('&'))
        return new OpCode(OpCode::VARIABLE, this->parseValue());
    if (this->accept('~'))
        return new OpCode(OpCode::OFFSET, this->parseValue());

    return new OpCode(OpCode::VALUE, this->parseValue());
}

Lexer::Lexer(const std::string& str) {
    debug("---- LEXER START ----");

    _ptr = &str.front();
    const char* const ep = &str.back();

    while (_ptr < ep) {
        const std::string cmd = this->parseString();
        debug("<COMMAND ", cmd, ">");

        OpCode* lhs = this->parseOpCode();

        if (this->accept(',')) {
            OpCode* rhs = this->parseOpCode();
            _commands.emplace_back(new Command(cmd, lhs, rhs));
        } else {
            _commands.emplace_back(new Command(cmd, lhs));
        }
    }

    debug("---- LEXER FINISHED ----");
}
