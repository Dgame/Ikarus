#include "Backend/Lexer.hpp"

#include <locale>
#include "util.hpp"

namespace Backend {
    void Lexer::scan(Token* tok) {
        if (this->accept('~')) {
            debug("found offset");

            tok->setType(Token::TILDE);
        } else if (this->accept('&')) {
            debug("found variable");

            tok->setType(Token::AMPERSAND);
        } else if (this->accept('.')) {
            tok->setType(Token::DOT);
        } else if (this->accept('-')) {
            tok->setType(Token::MINUS);
        } else if (this->accept(',')) {
            tok->setType(Token::COMMA);
        } else if (this->accept(';')) {
            tok->setType(Token::SEMICOLON);
        } else if (this->accept(':')) {
            tok->setType(Token::COLON);
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