#ifndef IKARUS_LOCATION_HPP
#define IKARUS_LOCATION_HPP

#include <locale>
#include "types.hpp"

class Location {
private:
    const char* _ptr = nullptr;
    const char* const _end = nullptr;

    u32_t _line = 0;

public:
    explicit Location(const char* pos, const char* const end) : _ptr(pos), _end(end) { }

    bool isValid() const {
        return _ptr < _end && this->get() != '\0';
    }

    bool is(char c) const {
        return *_ptr == c;
    }

    bool isSpace() const {
        return std::isspace(*_ptr);
    }

    bool isDigit() const {
        return std::isdigit(*_ptr);
    }

    bool isAlpha() const {
        return std::isalpha(*_ptr);
    }

    bool isAlphaNumeric() const {
        return std::isalnum(*_ptr);
    }

    char get() const {
        return *_ptr;
    }
    
    char peek(u32_t n = 1) const;

    char next();

    u32_t getLine() const {
        return _line;
    }
};

#endif //IKARUS_LOCATION_HPP
