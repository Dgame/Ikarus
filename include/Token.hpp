#ifndef IKARUS_TOKEN_HPP
#define IKARUS_TOKEN_HPP

#include "types.hpp"
#include <string>

class Token {
public:
    enum Type {
        NONE,
        INTEGER,
        DECIMAL,
        STRING,
        IDENTIFIER,
        AMPERSAND,
        AND,
        OR,
        TILDE,
        COMMA,
        SEMICOLON,
        ASSIGN,
        DOT,
        NOT,
        NEGATE,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        MODULO,
        INCREMENT,
        DECREMENT,
        OPEN_CURLY,
        CLOSE_CURLY,
        OPEN_BRACKET,
        CLOSE_BRACKET,
        OPEN_PAREN,
        CLOSE_PAREN,
    };

private:
    Type _type = NONE;

    std::string _identifier;

    union {
        i32_t _integer;
        f32_t _decimal;
    };

public:
    Token() = default;
    explicit Token(Type);

    void setType(Type type) {
        _type = type;
    }

    Type getType() const {
        return _type;
    }

    const std::string& getIdentifier() const {
        return _identifier;
    }

    f32_t getDecimal() const {
        return _decimal;
    }

    i32_t getInteger() const {
        return _integer;
    }

    void setIdentifier(const std::string&);
    void setString(const std::string&);
    void setDecimal(f32_t);
    void setInteger(i32_t);
};

#endif //IKARUS_TOKEN_HPP