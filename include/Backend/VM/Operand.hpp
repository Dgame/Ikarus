#ifndef IKARUS_OPERAND_HPP
#define IKARUS_OPERAND_HPP

#include "types.hpp"
#include <iostream>

namespace Backend {
    class Operand {
    public:
        enum {
            VALUE,
            OFFSET,
            VARIABLE
        };

    private:
        u16_t _type;

    public:
        explicit Operand(u16_t type) : _type(type) { }

        u16_t getType() const {
            return _type;
        }

        virtual void print(std::ostream&) const = 0;
    };
}

#endif //IKARUS_OPERAND_HPP
