#ifndef IKARUS_VALUE_HPP
#define IKARUS_VALUE_HPP

#include "Operand.hpp"

namespace Backend {
    template <typename T>
    class Value : public Operand {
    private:
        T _value;

    public:
        explicit Value(const T& value) : Operand(Operand::VALUE), _value(value) { }

        void print(std::ostream& out) const override {
            out << _value;
        }
    };
}

#endif //IKARUS_VALUE_HPP
