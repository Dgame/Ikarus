#include "Frontend/Keyword.hpp"
#include <map>

namespace {
    const std::map<std::string, Token::Type> Keywords = {
            {"let",      Token::MUTABLE},
            {"var",      Token::IMMUTABLE},
            {"function", Token::FUNCTION},
            {"if",       Token::IF},
            {"else",     Token::ELSE}
    };
}

namespace Frontend {
    namespace Keyword {
        Token::Type Get(const std::string& id) {
            auto it = Keywords.find(id);
            if (it != Keywords.end()) {
                return it->second;
            }

            return Token::NONE;
        }

        bool Is(const std::string& id) {
            return Get(id) != Token::NONE;
        }

        bool IsVariable(const std::string& id) {
            auto type = Get(id);

            return type == Token::MUTABLE || type == Token::IMMUTABLE;
        }
    }
}