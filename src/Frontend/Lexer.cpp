#include "Frontend/Lexer.hpp"
#include "util.hpp"

namespace Frontend {
    void Lexer::scan(Token* tok) {
        if (this->accept('=')) {
            if (this->accept('=')) {
                tok->setType(Token::EQUAL);
            } else {
                tok->setType(Token::ASSIGN);
            }
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
        } else if (this->accept('<')) {
            if (this->accept('=')) {
                tok->setType(Token::LOWER_EQUAL);
            } else {
                tok->setType(Token::LOWER);
            }
        } else if (this->accept('>')) {
            if (this->accept('=')) {
                tok->setType(Token::GREATER_EQUAL);
            } else {
                tok->setType(Token::GREATER);
            }
        } else if (this->accept('!')) {
            if (this->accept('=')) {
                tok->setType(Token::NOT_EQUAL);
            } else {
                tok->setType(Token::NOT);
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
        } else if (this->accept('?')) {
            tok->setType(Token::QUERY);
        } else if (this->accept(',')) {
            tok->setType(Token::COMMA);
        } else if (this->accept(':')) {
            tok->setType(Token::COLON);
        } else if (this->accept(';')) {
            this->skipLineComment();
            this->scan(tok);
        } else if (_location.is('"')) {
            this->parseString();
        } else if (_location.isAlpha()) {
            this->parseIdentifier();
        } else if (_location.isDigit()) {
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