#ifndef IKARUS_BACKEND_LEXER_HPP
#define IKARUS_BACKEND_LEXER_HPP

#include <string>
#include <vector>
#include "AbstractLexer.hpp"
#include "types.hpp"
#include "Token.hpp"

class Token;

namespace Backend {
    class Lexer : public AbstractLexer {
    protected:
        virtual void scan(Token*) override;

    public:
        explicit Lexer(const char*, const char* const);
    };
}

#endif //IKARUS_BACKEND_LEXER_HPP
