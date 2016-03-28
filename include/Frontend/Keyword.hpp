#ifndef IKARUS_KEYWORD_HPP
#define IKARUS_KEYWORD_HPP

#include <string>
#include "Token.hpp"

namespace Frontend {
    struct Keyword {
        enum {
            NONE,
            MUTABLE,
            IMMUTABLE,
            TRUE,
            FALSE,
            FUNCTION,
            IF,
            ELSE,
            WHILE
        };

        static u32_t Get(const std::string&);

        static bool Is(const std::string&);

        static bool IsVariable(const std::string&);
    };
}

#endif //IKARUS_KEYWORD_HPP
