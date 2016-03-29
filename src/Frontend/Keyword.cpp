#include "Frontend/Keyword.hpp"
#include <map>

namespace {
    using namespace Frontend;

    const std::map<std::string, u32_t> Keywords = {
            {"let",      Keyword::IMMUTABLE},
            {"var",      Keyword::MUTABLE},
            {"true",     Keyword::TRUE},
            {"false",    Keyword::FALSE},
            {"function", Keyword::FUNCTION},
            {"if",       Keyword::IF},
            {"else",     Keyword::ELSE},
            {"while",    Keyword::WHILE},
    };
}

namespace Frontend {
    u32_t Keyword::Get(const std::string& id) {
        auto it = Keywords.find(id);
        if (it != Keywords.end()) {
            return it->second;
        }

        return Keyword::NONE;
    }

    bool Keyword::Is(const std::string& id) {
        return Get(id) != Token::NONE;
    }

    bool Keyword::IsVariable(const std::string& id) {
        auto type = Get(id);

        return type == Keyword::MUTABLE || type == Keyword::IMMUTABLE;
    }
}