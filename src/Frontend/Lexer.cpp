#include "Frontend/Lexer.hpp"
#include "util.hpp"

namespace Frontend {
    bool Lexer::parse(Token& token) {
        this->skipSpaces();

        if (!this->isValid()) {
            return false;
        }

        if (this->accept('=')) {
            token.setType(Token::ASSIGN);
        } else if (this->accept('+')) {
            if (this->accept('+')) {
                token.setType(Token::INCREMENT);
            } else {
                token.setType(Token::PLUS);
            }
        } else if (this->accept('-')) {
            if (this->accept('-')) {
                token.setType(Token::DECREMENT);
            } else {
                token.setType(Token::MINUS);
            }
        } else if (this->accept('*')) {
            if (this->accept('*')) {
                token.setType(Token::POWER);
            } else {
                token.setType(Token::MULTIPLY);
            }
        } else if (this->accept('/')) {
            token.setType(Token::DIVIDE);
        } else if (this->accept('%')) {
            token.setType(Token::MODULO);
        } else if (this->accept('(')) {
            token.setType(Token::OPEN_PAREN);
        } else if (this->accept(')')) {
            token.setType(Token::CLOSE_PAREN);
        } else if (this->accept('[')) {
            token.setType(Token::OPEN_BRACKET);
        } else if (this->accept(']')) {
            token.setType(Token::CLOSE_BRACKET);
        } else if (this->accept('{')) {
            token.setType(Token::OPEN_CURLY);
        } else if (this->accept('}')) {
            token.setType(Token::CLOSE_CURLY);
        } else if (*_ptr == '"') {
            this->parseString(token);
        } else if (std::isalpha(*_ptr)) {
            this->parseIdentifier(token);
        } else if (std::isdigit(*_ptr)) {
            debug("found numeric");

            this->parseNumeric(token);
        } else {
            error("Unexpected Token ", *_ptr, _ptr);
        }

        return token.getType() != Token::NONE;
    }

    Lexer::Lexer(const char* pos, const char* const end) : AbstractLexer(pos, end) {
        debug("---- LEXER START ----");

        while (this->isValid()) {
            Token token;
            if (this->parse(token)) {
                _token.push_back(token);
            }
        }

        debug("---- LEXER FINISHED ----");
    }
}