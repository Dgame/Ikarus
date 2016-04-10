#ifndef IKARUS_OFFSET_HPP
#define IKARUS_OFFSET_HPP

#include "Operand.hpp"

namespace Backend {
    class Offset : public Operand {
    private:
        size_t _offset;

        static size_t& Counter() {
            static size_t counter = 0;

            return counter;
        }

    public:
        explicit Offset() : Offset(Counter()++) { }
        explicit Offset(size_t offset) : Operand(Operand::OFFSET), _offset(offset) { }

        void print(std::ostream& out) const override {
            out << '~' << _offset;
        }
    };
}

#endif //IKARUS_OFFSET_HPP