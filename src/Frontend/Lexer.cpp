#include "Frontend/Lexer.hpp"
#include "util.hpp"

namespace Frontend {
    void Lexer::scan(Token* tok) {
        if (this->accept('=')) {
            tok->setType(Token::ASSIGN);
        } else if (this->accept('+')) {
            if (this->accept('+')) {
                tok->setType(Token::INCREMENT);
            } else {
                tok->setType(Token::PLUS);
            }
        } else if (this->accept('-')) {
            if (this->accept('-')) {
                tok->setType(Token::DECREMENT);
            } else {
                tok->setType(Token::MINUS);
            }
        } else if (this->accept('*')) {
            if (this->accept('*')) {
                tok->setType(Token::POWER);
            } else {
                tok->setType(Token::MULTIPLY);
            }
        } else if (this->accept('/')) {
            tok->setType(Token::DIVIDE);
        } else if (this->accept('%')) {
            tok->setType(Token::MODULO);
        } else if (this->accept('(')) {
            tok->setType(Token::OPEN_PAREN);
        } else if (this->accept(')')) {
            tok->setType(Token::CLOSE_PAREN);
        } else if (this->accept('[')) {
            tok->setType(Token::OPEN_BRACKET);
        } else if (this->accept(']')) {
            tok->setType(Token::CLOSE_BRACKET);
        } else if (this->accept('{')) {
            tok->setType(Token::OPEN_CURLY);
        } else if (this->accept('}')) {
            tok->setType(Token::CLOSE_CURLY);
        } else if (this->accept('!')) {
            tok->setType(Token::NOT);
        } else if (this->accept('?')) {
            tok->setType(Token::QUERY);
        } else if (*_ptr == '"') {
            this->parseString();
        } else if (std::isalpha(*_ptr)) {
            this->parseIdentifier();
        } else if (std::isdigit(*_ptr)) {
            debug("found numeric");

            this->parseNumeric();
        } else {
            tok->setType(Token::NONE);
        }
    }

    Lexer::Lexer(const char* pos, const char* const end) : AbstractLexer(pos, end) {
        this->next();
    }
}