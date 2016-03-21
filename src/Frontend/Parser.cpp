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

namespace Frontend {
    void Parser::pushScope() {
        _scope = new Scope(_scope);
        _scopes.emplace_back(_scope);
    }

    void Parser::popScope() {
        _scope = _scope->getPredecessor();
    }

    void Parser::parse(Lexer& lexer) {

    }

    void Parser::parseVarDecl(Lexer& lexer) {
    }

    Expression* Parser::parseExpr(Lexer& lexer) {
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
            exp = this->parseExpr(lexer);
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