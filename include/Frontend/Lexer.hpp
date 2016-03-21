#ifndef IKARUS_FRONTEND_LEXER_HPP
#define IKARUS_FRONTEND_LEXER_HPP

#include "AbstractLexer.hpp"

namespace Frontend {
    class Lexer : public AbstractLexer {
    protected:
        virtual void scan(Token*) override;

    public:
        explicit Lexer(const char*, const char* const);
    };
}

#endif //IKARUS_FRONTEND_LEXER_HPP
