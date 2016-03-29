#ifndef IKARUS_TOKEN_HPP
#define IKARUS_TOKEN_HPP

#include "types.hpp"
#include <string>
#include <memory>

class Token {
public:
    enum Type {
        NONE,
        INTEGER,
        DECIMAL,
        STRING,
        IDENTIFIER,
        AMPERSAND,
        TILDE,
        COMMA,
        COLON,
        ASSIGN,
        DOT,
        NOT,
        QUERY,
        NEGATE,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        MODULO,
        INCREMENT,
        DECREMENT,
        POWER,
        OPEN_CURLY,
        CLOSE_CURLY,
        OPEN_BRACKET,
        CLOSE_BRACKET,
        OPEN_PAREN,
        CLOSE_PAREN,
        LOWER,
        LOWER_EQUAL,
        GREATER,
        GREATER_EQUAL,
        EQUAL,
        NOT_EQUAL,
    };

private:
    Type _type = NONE;

    std::string _identifier;
    i32_t _integer = 0;
    f32_t _decimal = 0;

public:
    std::unique_ptr<Token> next;

    Token() = default;

    explicit Token(Type);

    static std::string AsString(Type);

    std::string asString() const;

    void setType(Type type) {
        _type = type;
    }

    Type getType() const {
        return _type;
    }

    bool is(Type type) const {
        return _type == type;
    }

    bool isKeyword() const;

    u32_t asKeyword() const;

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
