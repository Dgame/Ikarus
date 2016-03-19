#ifndef IKARUS_LEXER_H
#define IKARUS_LEXER_H

#include <vector>

#include "Token.hpp"
#include "types.hpp"

class AbstractLexer {
protected:
    std::vector<Token> _token;
    size_t _index = 0;

    const char* _ptr = nullptr;
    const char* const _end = nullptr;

    void skipSpaces();

    bool accept(char);

    void expect(char);

    bool isValid() const;

    virtual void parsePrefix();

    virtual void parseIdentifier(Token&);

    virtual void parseString(Token&);

    virtual void parseNumeric(Token&);

public:
    explicit AbstractLexer(const char*, const char* const);

    void setIndex(size_t index) {
        _index = index;
    }

    size_t getIndex() const {
        return _index;
    }

    const Token* getToken() const;

    const Token* nextToken();

};

#endif //IKARUS_LEXER_H
