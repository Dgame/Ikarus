#include "Location.hpp"

char Location::peek(u32_t n) const {
    if ((_ptr + n) >= _end)
        return '\0';
    return *(_ptr + n);
}

char Location::next() {
    if (!this->isValid())
        return '\0';

    _ptr++;
    const char c = *_ptr;
    switch (c) {
        case '\n':
            _line++;
            break;
        case '\r':
            if (*(_ptr + 1) != '\n')
                _line++;
        default:
            break;
    }

    return c;
}