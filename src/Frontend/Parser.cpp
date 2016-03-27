#include "Frontend/Parser.hpp"
#include "AddExpression.hpp"
#include "SubtractExpression.hpp"
#include "MultiplyExpression.hpp"
#include "DivideExpression.hpp"
#include "ModuloExpression.hpp"
#include "NumericExpression.hpp"
#include "NegateExpression.hpp"
#include "NotExpression.hpp"
#include "ArrayExpression.hpp"
#include "IndexAssignExpression.hpp"
#include "IndexAccessExpression.hpp"
#include "Frontend/Keyword.hpp"

namespace Frontend {
    void Parser::pushScope() {
        _scope = new Scope(_scope);
        _scopes.emplace_back(_scope);
    }

    void Parser::popScope() {
        _scope = _scope->getPredecessor();
        enforce(is(_scope), "Empty Scope?!");
    }

    void Parser::parse() {
        const Token* tok = nullptr;
        do {
            tok = _lexer.getToken();
            if (tok->is(Token::IDENTIFIER)) {
                this->parseIdentifier();
            } else {
                error("#1 Not implemented @ ", _lexer.getLocation().getLine());
                break;
            }
        } while (!tok->is(Token::NONE));
    }

    void Parser::parseIdentifier() {
        auto tok = _lexer.getToken();
        enforce(tok->is(Token::IDENTIFIER), "Should be an identifier @ ", _lexer.getLocation().getLine());

        const std::string& id = tok->getIdentifier();
        if (Keyword::Is(id)) {
            switch (Keyword::Get(id)) {
                case Token::IF:
                case Token::ELSE:
                case Token::FUNCTION:
                case Token::WHILE:
//                    this->parseWhile();
                    error("#2 Not implemented @ ", _lexer.getLocation().getLine());
                    break;
                default:
                    this->parseVariableDeclaration();
            }
        } else {
            this->parseVariableDeclaration();
        }
    }

    void Parser::parseWhile() {
        auto tok = _lexer.getToken();
        enforce(tok->is(Token::IDENTIFIER), "Should be an identifier @ ", _lexer.getLocation().getLine());

        // TODO: implement
    }

    void Parser::parseVariableDeclaration() {
        const Token* tok = _lexer.getToken();
        enforce(tok->is(Token::IDENTIFIER), "Should be an identifier @ ", _lexer.getLocation().getLine());

        const std::string id = tok->getIdentifier();
        if (Keyword::IsVariable(id)) {
            this->assignNewVariable(id);
        } else {
            this->assignExistingVariable(id);
        }
    }

    void Parser::assignNewVariable(const std::string& id) {
        _lexer.next();

        const std::string name = _lexer.getToken()->getIdentifier();
        enforce(!is(_scope->findVariable(name)), "A variable with name ", name, " already exists @ ", _lexer.getLocation().getLine());

        _lexer.next();
        _lexer.expect(Token::ASSIGN);

        auto exp = this->parseExpression();
        auto vd = new VariableDeclaration(name, exp);
        if (Keyword::Get(id) == Token::IMMUTABLE) {
            vd->setStorageClass(StorageClass.IMMUTABLE);
        }
        _scope->addVariable(vd);
    }

    void Parser::assignExistingVariable(const std::string& id) {
        auto vde = _scope->findVariable(id);
        enforce(is(vde), "No such variable: ", id, " @ ", _lexer.getLocation().getLine());
        enforce(!vde->isConst(), "Variable ", id, " is const @ ", _lexer.getLocation().getLine());

        _lexer.next();

        Expression* index = nullptr;
        if (_lexer.getToken()->is(Token::OPEN_BRACKET)) {
            index = this->parseIndexExpression();
        }

        _lexer.expect(Token::ASSIGN);

        auto exp = this->parseExpression();
        if (is(index)) {
            exp = new IndexAssignExpression(vde, index, exp);
        }

        auto vd = vde->child(exp);
        if (is(index)) {
            _scope->add(vd);
        } else {
            _scope->addVariable(vd);
        }
    }

    Expression* Parser::parseIndexExpression() {
        _lexer.expect(Token::OPEN_BRACKET);
        Expression* exp = this->parseExpression();
        _lexer.expect(Token::CLOSE_BRACKET);

        return exp;
    }

    Expression* Parser::parseArrayExpression() {
        _lexer.expect(Token::OPEN_BRACKET);

        ArrayExpression* ae = new ArrayExpression();
        while (!_lexer.getToken()->is(Token::CLOSE_BRACKET)) {
            Expression* exp = this->parseExpression();
            ae->append(exp);

            if (!_lexer.accept(Token::COMMA))
                break;
        }

        _lexer.expect(Token::CLOSE_BRACKET);

        return ae;
    }

    Expression* Parser::parseExpression() {
        if (_lexer.getToken()->is(Token::OPEN_BRACKET)) {
            return this->parseArrayExpression();
        }

        Expression* lhs = this->parseTerm();
        enforce(is(lhs), "Empty Left-Hand-Expression @ ", _lexer.getLocation().getLine());

        while (true) {
            if (_lexer.accept(Token::PLUS)) {
                Expression* rhs = this->parseTerm();
                enforce(is(rhs), "Expected factor after + @ ", _lexer.getLocation().getLine());
                lhs = new AddExpression(lhs, rhs);

                continue;
            }

            if (_lexer.accept(Token::MINUS)) {
                Expression* rhs = this->parseTerm();
                enforce(is(rhs), "Expected factor after - @ ", _lexer.getLocation().getLine());
                lhs = new SubtractExpression(rhs, lhs);

                continue;
            }

            break;
        }

        return lhs;
    }

    Expression* Parser::parseTerm() {
        Expression* lhs = this->parseFactor();
        enforce(is(lhs), "[Term] Empty Left-Hand-Expression @ ", _lexer.getLocation().getLine());

        while (true) {
            if (_lexer.accept(Token::MULTIPLY)) {
                Expression* rhs = this->parseFactor();
                enforce(is(rhs), "Expected factor after * @ ", _lexer.getLocation().getLine());
                lhs = new MultiplyExpression(lhs, rhs);

                continue;
            }

            if (_lexer.accept(Token::DIVIDE)) {
                Expression* rhs = this->parseFactor();
                enforce(is(rhs), "Expected factor after / @ ", _lexer.getLocation().getLine());
                lhs = new DivideExpression(rhs, lhs);

                continue;
            }

            if (_lexer.accept(Token::MODULO)) {
                Expression* rhs = this->parseFactor();
                enforce(is(rhs), "Expected factor after % @ ", _lexer.getLocation().getLine());
                lhs = new ModuloExpression(rhs, lhs);

                continue;
            }

            break;
        }

        return lhs;
    }

    Expression* Parser::parseFactor() {
        bool op_neg = false;
        bool op_not = false;

        while (true) {
            if (_lexer.accept(Token::NOT)) {
                op_not = !op_not;
            } else if (_lexer.accept(Token::NEGATE)) {
                op_neg = !op_neg;
            } else {
                break;
            }
        }

        Expression* exp = nullptr;

        const Token* tok = _lexer.getToken();
        if (tok->is(Token::INTEGER)) {
            exp = new NumericExpression(tok->getInteger());
            _lexer.next();
        } else if (tok->is(Token::DECIMAL)) {
            exp = new NumericExpression(tok->getDecimal());
            _lexer.next();
        } else if (_lexer.accept(Token::OPEN_PAREN)) {
            exp = this->parseExpression();
            _lexer.expect(Token::CLOSE_PAREN);
        } else if (tok->is(Token::IDENTIFIER)) {
            exp = this->parseVariableExpression();
        }

        if (op_not) {
            enforce(is(exp), "Nothing that can be noted @ ", _lexer.getLocation().getLine());
            exp = new NotExpression(exp);
        }

        if (op_neg) {
            enforce(is(exp), "Nothing that can be negated @ ", _lexer.getLocation().getLine());
            exp = new NegateExpression(exp);
        }

        enforce(is(exp), "No Expression found @ ", _lexer.getLocation().getLine());

        return exp;
    }

    Expression* Parser::parseVariableExpression() {
        enforce(_lexer.getToken()->is(Token::IDENTIFIER), "Expected identifier as variable name @ ", _lexer.getLocation().getLine());

        const std::string& id = _lexer.getToken()->getIdentifier();

        auto vde = _scope->findVariable(id);
        enforce(is(vde), "No variable with name ", id, " exists @ ", _lexer.getLocation().getLine());

        _lexer.next();

        if (_lexer.getToken()->is(Token::OPEN_BRACKET)) {
            Expression* index = this->parseIndexExpression();

            return new IndexAccessExpression(vde, index);
        }

        return new VariableExpression(vde);
    }

    Parser::Parser(const char* pos, const char* const end) : _lexer(pos, end) {
        this->pushScope();
        this->parse();
    }

    void Parser::eval(std::ostream& out) {
        for (auto& scope : _scopes) {
            scope->eval(out);
        }
    }
}