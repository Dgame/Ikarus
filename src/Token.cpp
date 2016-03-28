#include "Token.hpp"
#include "Frontend/Keyword.hpp"

Token::Token(Type type) : _type(type) { }

std::string Token::AsString(Type type) {
    switch (type) {
        case NONE:
            return "<None>";
        case INTEGER:
            return ">Integer>";
        case DECIMAL:
            return "<Decimal>";
        case STRING:
            return "<String>";
        case IDENTIFIER:
            return "<Identifier>";
        case AMPERSAND:
            return "&";
        case TILDE:
            return "~";
        case COMMA:
            return ",";
        case COLON:
            return ":";
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
        case LOWER:
            return "<";
        case LOWER_EQUAL:
            return "<=";
        case GREATER:
            return ">";
        case GREATER_EQUAL:
            return ">=";
        case EQUAL:
            return "==";
        case NOT_EQUAL:
            return "!=";
    }
}

std::string Token::asString() {
    return Token::AsString(_type);
}

bool Token::isKeyword() const {
    return this->is(Token::IDENTIFIER) && Frontend::Keyword::Is(_identifier);
}

u32_t Token::asKeyword() const {
    if (!this->isKeyword()) {
        return Frontend::Keyword::NONE;
    }

    return Frontend::Keyword::Get(_identifier);
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
