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
            u32_t _offset;
            u64_t _vid;
            f32_t _number;
        };

    public:
        explicit Operand(Type type) : _type(type) { }

        static Operand Number(f32_t);

        static Operand Offset(u32_t);

        static Operand Variable(u64_t);

        void print(std::ostream&) const;
    };
}

#endif //IKARUS_OPERAND_HPP
