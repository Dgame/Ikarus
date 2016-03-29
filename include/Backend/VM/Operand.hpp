#ifndef IKARUS_OPERAND_HPP
#define IKARUS_OPERAND_HPP

#include "types.hpp"
#include <ostream>

namespace Backend {
    class Operand {
    public:
        enum Type {
            NONE,
            OFFSET,
            VARIABLE,
            NUMBER
        };

    private:
        Type _type;

        union {
            size_t _offset;
            size_t _vid;
            f32_t _number;
        };

    public:
        explicit Operand(Type type) : _type(type) { }

        static Operand Number(f32_t);

        static Operand Offset(size_t);

        static Operand Variable(size_t);

        void print(std::ostream&) const;
    };
}

#endif //IKARUS_OPERAND_HPP
