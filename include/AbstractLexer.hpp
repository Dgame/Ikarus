#ifndef IKARUS_LEXER_H
#define IKARUS_LEXER_H

#include <vector>

#include "Token.hpp"
#include "types.hpp"

class AbstractLexer {
protected:
    std::unique_ptr<Token> _token;

    const char* _ptr = nullptr;
    const char* const _end = nullptr;

    void skipSpaces();

    virtual void parseIdentifier();

    virtual void parseString();

    virtual void parseNumeric();

    virtual void scan(Token*) = 0;

public:
    explicit AbstractLexer(const char*, const char* const);

    bool isValid() const {
        return _ptr <= _end && *_ptr != '\0';
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
