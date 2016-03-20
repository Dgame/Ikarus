#include "Backend/Lexer.hpp"

#include <locale>
#include "util.hpp"

namespace Backend {
    bool Lexer::parse(Token& token) {
        this->skipSpaces();

        if (!this->isValid()) {
            return false;
        }

        if (this->accept('~')) {
            debug("found offset");

            token.setType(Token::TILDE);
        } else if (this->accept('&')) {
            debug("found variable");

            token.setType(Token::AMPERSAND);
        } else if (this->accept('.')) {
            token.setType(Token::DOT);
        } else if (this->accept(',')) {
            token.setType(Token::COMMA);
        } else if (this->accept(';')) {
            token.setType(Token::SEMICOLON);
        } else if (this->accept(':')) {
            token.setType(Token::COLON);
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