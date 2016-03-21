#ifndef IKARUS_KEYWORD_HPP
#define IKARUS_KEYWORD_HPP

#include <string>
#include "Token.hpp"

namespace Frontend {
    namespace Keyword {
        Token::Type Get(const std::string&);

        bool Is(const std::string&);

        bool IsVariable(const std::string&);
    }
}

#endif //IKARUS_KEYWORD_HPP
