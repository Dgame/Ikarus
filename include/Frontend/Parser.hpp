#ifndef IKARUS_PARSER_HPP
#define IKARUS_PARSER_HPP

#include <vector>
#include <memory>
#include "Frontend/Scope.hpp"

class Expression;

namespace Frontend {
    class Lexer;

    class Parser {
    private:
        std::vector<std::unique_ptr<Scope>> _scopes;
        Scope* _scope = nullptr;

        void pushScope();
        void popScope();

        void parse(Lexer&);
        void parseVarDecl(Lexer&);
        Expression* parseExpr(Lexer&);
        Expression* parseTerm(Lexer&);
        Expression* parseFactor(Lexer&);

    public:
        explicit Parser(const char*, const char* const);
    };
}

#endif //IKARUS_PARSER_HPP
