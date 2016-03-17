#ifndef IKARUS_LEXER_HPP
#define IKARUS_LEXER_HPP

#include <string>
#include <vector>
#include "AbstractLexer.hpp"
#include "types.hpp"
#include "Token.hpp"

class Token;

namespace Backend {
    class Lexer : public AbstractLexer {
    private:
        bool parse(Token&);

    public:
        explicit Lexer(const char*, const char* const);
    };
}

#endif //IKARUS_LEXER_HPP
