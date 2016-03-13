#include "Token.hpp"

Token::Token(Type type) : _type(type) { }

void Token::setIdentifier(const std::string& id) {
    _identifier = id;

    this->setType(IDENTIFIER);
}

void Token::setString(const std::string& id) {
    _identifier = id;

    this->setType(STRING);
}

void Token::setDecimal(f32_t num) {
    _decimal = num;

    this->setType(DECIMAL);
}

void Token::setInteger(i32_t num) {
    _integer = num;

    this->setType(INTEGER);
}
