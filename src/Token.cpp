#include "Token.hpp"

Token::Token(Type type) : _type(type) { }

std::string Token::AsString(Type type) {
    switch (type) {
        case NONE:
            return "None";
        case INTEGER:
            return "Integer";
        case DECIMAL:
            return "Decimal";
        case STRING:
            return "String";
        case IDENTIFIER:
            return "Identifier";
        case AMPERSAND:
            return "&";
        case TILDE:
            return "~";
        case COMMA:
            return ",";
        case COLON:
            return ":";
        case SEMICOLON:
            return ";";
        case ASSIGN:
            return "=";
        case DOT:
            return ".";
        case NOT:
            return "!";
        case QUERY:
            return "?";
        case NEGATE:
            return "-";
        case PLUS:
            return "+";
        case MINUS:
            return "-";
        case MULTIPLY:
            return "*";
        case DIVIDE:
            return "/";
        case MODULO:
            return "%";
        case INCREMENT:
            return "++";
        case DECREMENT:
            return "--";
        case POWER:
            return "**";
        case OPEN_CURLY:
            return "{";
        case CLOSE_CURLY:
            return "}";
        case OPEN_BRACKET:
            return "[";
        case CLOSE_BRACKET:
            return "]";
        case OPEN_PAREN:
            return "(";
        case CLOSE_PAREN:
            return ")";
        case MUTABLE:
            return "var";
        case IMMUTABLE:
            return "let";
        case FUNCTION:
            return "function";
        case IF:
            return "if";
        case ELSE:
            return "else";
        case WHILE:
            return "while";
    }
}

std::string Token::asString() {
    return Token::AsString(_type);
}

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
