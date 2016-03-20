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
        const Token* tok = lexer.accept(Token::IDENTIFIER);
        if (tok) {

        }
    }

    Expression* Parser::parseExpr(Lexer& lexer) {
        Expression* lhs = this->parseTerm(lexer);
        if (!lhs) {
            return nullptr;
        }

        while (true) {
            if (lexer.accept(Token::PLUS)) {
                Expression* rhs = this->parseTerm(lexer);
                if (!rhs) {
                    error("Expected factor after +");
                    break;
                }

                lhs = new AddExpression(lhs, rhs);

                lexer.nextToken();

                continue;
            }

            if (lexer.accept(Token::MINUS)) {
                Expression* rhs = this->parseTerm(lexer);
                if (!rhs) {
                    error("Expected factor after -");
                    break;
                }

                lhs = new SubtractExpression(rhs, lhs);

                lexer.nextToken();

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
                if (!rhs) {
                    error("Expected factor after *");
                    break;
                }

                lhs = new MultiplyExpression(lhs, rhs);

                lexer.nextToken();

                continue;
            }

            if (lexer.accept(Token::DIVIDE)) {
                Expression* rhs = this->parseFactor(lexer);
                if (!rhs) {
                    error("Expected factor after /");
                    break;
                }

                lhs = new DivideExpression(rhs, lhs);

                lexer.nextToken();

                continue;
            }

            if (lexer.accept(Token::MODULO)) {
                Expression* rhs = this->parseFactor(lexer);
                if (!rhs) {
                    error("Expected factor after %");
                    break;
                }

                lhs = new ModuloExpression(rhs, lhs);

                lexer.nextToken();

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
        const Token* tok = nullptr;

        if ((tok = lexer.accept(Token::INTEGER)))
            exp = new NumericExpression(tok->getInteger());
        else if ((tok = lexer.accept(Token::DECIMAL)))
            exp = new NumericExpression(tok->getDecimal());
        else if (lexer.accept(Token::OPEN_CURLY)) {
            exp = this->parseExpr(lexer);
            lexer.expect(Token::CLOSE_CURLY);
        }

        if (op_not) {
            if (!exp)
                error("Nothing that can be noted");
            else
                exp = new NotExpression(exp);
        }

        if (op_neg) {
            if (!exp)
                error("Nothing that can be negated");
            else
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