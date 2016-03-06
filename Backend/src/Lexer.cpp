//
// Created by Randy on 05.03.2016.
//

#include <locale>
#include <Lexer.hpp>
#include <util.hpp>
#include <NumericValue.hpp>

namespace ik {
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
        while (std::isalpha(*_ptr)) {
            value += *_ptr;
            _ptr++;
        }

        return value;
    }

    int Lexer::parseNumber() {
        this->skipSpaces();

        int value = 0;
        while (isdigit(*_ptr)) {
            value *= 10;
            value += static_cast<int>(*_ptr - '0');

            _ptr++;
        }

        return value;
    }

    Value* Lexer::parseValue() {
        return new NumericValue(this->parseNumber());
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
        _ptr = &str.front();
        const char* const ep = &str.back();

        while (_ptr < ep) {
            const std::string cmd = this->parseString();
            writeln("<COMMAND ", cmd, ">");

            OpCode* lhs = this->parseOpCode();

            if (this->accept(',')) {
                OpCode* rhs = this->parseOpCode();
                _commands.emplace_back(new Command(cmd, lhs, rhs));
            } else {
                _commands.emplace_back(new Command(cmd, lhs));
            }
        }
    }
}