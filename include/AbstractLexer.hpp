#ifndef IKARUS_LEXER_H
#define IKARUS_LEXER_H

#include <vector>

#include "Token.hpp"
#include "Location.hpp"
#include "types.hpp"

class AbstractLexer {
protected:
    std::unique_ptr<Token> _token;

    Location _location;

    void skipSpaces();

    virtual void parseIdentifier();

    virtual void parseString();

    virtual void parseNumeric();

    virtual void scan(Token*) = 0;

public:
    explicit AbstractLexer(const char*, const char* const);

    const Location& getLocation() const {
        return _location;
    }

    bool accept(char);

    void expect(char);

    Token* getToken() {
        return _token.get();
    }

    Token* peek(Token*);

    Token::Type peekNext();

    Token::Type peekNext2();

    Token::Type next();

    bool accept(Token::Type);
    void expect(Token::Type);
};

#endif //IKARUS_LEXER_H
