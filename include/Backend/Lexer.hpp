#ifndef IKARUS_LEXER_HPP
#define IKARUS_LEXER_HPP

#include <string>
#include <vector>
#include "types.hpp"
#include "Token.hpp"

class Expression;
class Declaration;
class Token;

class Lexer {
private:
    std::vector<Token> _token;
    u32_t _index = 0;

    const char* _ptr = nullptr;
    const char* const _end = nullptr;

    void skipSpaces();
    bool accept(char);
    void expect(char);
    bool isValid() const;

    void parsePrefix();
    void parseIdentifier(Token&);
    void parseString(Token&);
    void parseNumeric(Token&);

    bool parse(Token&);

public:
    explicit Lexer(const char*, const char* const);

    void setIndex(u32_t index) {
        _index = 0;
    }

    u32_t getIndex() const {
        return _index;
    }

    const Token* getToken() const;
    const Token* nextToken();
};

#endif //IKARUS_LEXER_HPP
