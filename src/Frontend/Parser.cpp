#include <StorageClass.hpp>
#include "Frontend/Parser.hpp"
#include "Frontend/Lexer.hpp"
#include "AddExpression.hpp"
#include "SubtractExpression.hpp"
#include "MultiplyExpression.hpp"
#include "DivideExpression.hpp"
#include "ModuloExpression.hpp"
#include "NumericExpression.hpp"
#include "NegateExpression.hpp"
#include "NotExpression.hpp"
#include "VariableDeclaration.hpp"
#include "Frontend/Keyword.hpp"

namespace Frontend {
    void Parser::pushScope() {
        _scope = new Scope(_scope);
        _scopes.emplace_back(_scope);
    }

    void Parser::popScope() {
        _scope = _scope->getPredecessor();
    }

    void Parser::parse(Lexer& lexer) {
        if (lexer.peekNext() == Token::IDENTIFIER) {
            this->parseIdentifier(lexer);
        }
    }

    void Parser::parseIdentifier(Lexer& lexer) {
        const Token* tok = lexer.getToken();
        enforce(tok->is(Token::IDENTIFIER), "Should be an identifier");

        const std::string& id = tok->getIdentifier();
        if (Keyword::Is(id)) {
            switch (Keyword::Get(id)) {
                case Token::IF:
                case Token::ELSE:
                case Token::FUNCTION:
                case Token::WHILE:
                    error("Not implemented");
                    break;
                default:
                    this->parseVarDeclaration(lexer);
            }
        } else {
            error("Unexpected identifier");
        }
    }

    void Parser::parseVarDeclaration(Lexer& lexer) {
        const Token* tok = lexer.getToken();
        enforce(tok->is(Token::IDENTIFIER), "Should be an identifier");

        const std::string id = tok->getIdentifier();
        if (Keyword::IsVariable(id)) {
            this->assignNewVariable(lexer, id);
        } else {
            this->assignExistingVariable(lexer, id);
        }
    }

    void Parser::assignNewVariable(Lexer& lexer, const std::string& id) {
        lexer.next();
        const std::string name = lexer.getToken()->getIdentifier();
        enforce(_scope->findVariable(name) == nullptr, "A variable with name ", name, " already exists");
        lexer.next();
        lexer.expect(Token::ASSIGN);

        auto exp = this->parseExpression(lexer);

        auto vd = new VariableDeclaration(name, exp);
        if (Keyword::Get(id) == Token::IMMUTABLE)
            vd->setStorageClass(StorageClass.IMMUTABLE);
        _scope->addVariable(vd);
    }

    void Parser::assignExistingVariable(Lexer& lexer, const std::string& id) {
        VariableDeclaration* vd = _scope->findVariable(id);
        enforce(vd != nullptr, "No such variable: ", id);
        enforce(!vd->isConst(), "Variable ", id, " is const");

        lexer.next();
        lexer.expect(Token::ASSIGN);

        auto exp = this->parseExpression(lexer);
        vd->setExpression(exp);
    }

    Expression* Parser::parseExpression(Lexer& lexer) {
        Expression* lhs = this->parseTerm(lexer);
        if (!lhs) {
            return nullptr;
        }

        while (true) {
            if (lexer.accept(Token::PLUS)) {
                Expression* rhs = this->parseTerm(lexer);
                enforce(rhs != nullptr, "Expected factor after +");
                lhs = new AddExpression(lhs, rhs);

                lexer.next();

                continue;
            }

            if (lexer.accept(Token::MINUS)) {
                Expression* rhs = this->parseTerm(lexer);
                enforce(rhs != nullptr, "Expected factor after -");
                lhs = new SubtractExpression(rhs, lhs);

                lexer.next();

                continue;
            }

            break;
        }

        return lhs;
    }

    Expression* Parser::parseTerm(Lexer& lexer) {
        Expression* lhs = this->parseFactor(lexer);
        if (!lhs)
            return nullptr;

        while (true) {
            if (lexer.accept(Token::MULTIPLY)) {
                Expression* rhs = this->parseFactor(lexer);
                enforce(rhs != nullptr, "Expected factor after *");
                lhs = new MultiplyExpression(lhs, rhs);

                lexer.next();

                continue;
            }

            if (lexer.accept(Token::DIVIDE)) {
                Expression* rhs = this->parseFactor(lexer);
                enforce(rhs != nullptr, "Expected factor after /");
                lhs = new DivideExpression(rhs, lhs);

                lexer.next();

                continue;
            }

            if (lexer.accept(Token::MODULO)) {
                Expression* rhs = this->parseFactor(lexer);
                enforce(rhs != nullptr, "Expected factor after %");
                lhs = new ModuloExpression(rhs, lhs);

                lexer.next();

                continue;
            }

            break;
        }

        return lhs;
    }

    Expression* Parser::parseFactor(Lexer& lexer) {
        bool op_neg = false;
        bool op_not = false;

        if (lexer.accept(Token::NOT)) {
            op_not = true;
        }

        if (lexer.accept(Token::NEGATE)) {
            op_neg = true;
        }

        Expression* exp = nullptr;

        const Token* tok = lexer.getToken();
        if (tok->is(Token::INTEGER)) {
            exp = new NumericExpression(tok->getInteger());
            lexer.next();
        } else if (tok->is(Token::DECIMAL)) {
            exp = new NumericExpression(tok->getDecimal());
            lexer.next();
        } else if (lexer.accept(Token::OPEN_CURLY)) {
            exp = this->parseExpression(lexer);
            lexer.expect(Token::CLOSE_CURLY);
        }

        if (op_not) {
            enforce(exp != nullptr, "Nothing that can be noted");
            exp = new NotExpression(exp);
        }

        if (op_neg) {
            enforce(exp != nullptr, "Nothing that can be negated");
            exp = new NegateExpression(exp);
        }

        return exp;
    }

    Parser::Parser(const char* pos, const char* const end) {
        Lexer lexer(pos, end);

        this->pushScope();
        this->parse(lexer);
    }
}