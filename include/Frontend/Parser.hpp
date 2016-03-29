#ifndef IKARUS_PARSER_HPP
#define IKARUS_PARSER_HPP

#include <vector>
#include <memory>
#include <Declaration/VariableDeclaration.hpp>
#include "Frontend/Scope.hpp"
#include "Frontend/Lexer.hpp"

class Expression;

namespace Frontend {
    class Parser {
    private:
        Scope* _scope = nullptr;
        Lexer _lexer;

        void pushScope();
        void popScope();

        void parse();
        void parseIdentifier();

        void parseWhileStatement();

        void parseVariableDeclaration();
        void assignNewVariable(const std::string&);
        void assignExistingVariable(const std::string&);

        u32_t parsePrefix();

        Expression* parseKeywordExpression();
        Expression* parseIndexExpression();
        Expression* parseArrayExpression();
        Expression* parseExpression();
        Expression* parseTerm();
        Expression* parseFactor();
        Expression* parseVariableExpression();

    public:
        explicit Parser(const char*, const char* const);
        ~Parser();

        void eval(std::ostream&);
    };
}

#endif //IKARUS_PARSER_HPP
