#ifndef IKARUS_PARSER_HPP
#define IKARUS_PARSER_HPP

#include <vector>
#include <memory>
#include <Expression/Expression.hpp>
#include "Frontend/Scope.hpp"
#include "Frontend/Lexer.hpp"

class Expression;

namespace Frontend {
    class Parser {
    private:
        Scope* _scope = nullptr;
        std::vector<std::unique_ptr<Scope>> _scopes;
        Lexer _lexer;

        void pushScope();
        void popScope();

        void parse();
        void parseIdentifier();

        void parseWhile();
        void parseVarDeclaration();
        void assignNewVariable(const std::string&);
        void assignExistingVariable(const std::string&);

        Expression* parseIndexExpression();
        Expression* parseArrayExpression();
        Expression* parseExpression();
        Expression* parseTerm();
        Expression* parseFactor();

    public:
        explicit Parser(const char*, const char* const);

        void eval(std::ostream&);
    };
}

#endif //IKARUS_PARSER_HPP
