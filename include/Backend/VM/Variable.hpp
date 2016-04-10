#ifndef IKARUS_VARIABLE_HPP
#define IKARUS_VARIABLE_HPP

#include "Operand.hpp"

namespace Backend {
    class Variable : public Operand {
    private:
        size_t _vid;

    public:
        explicit Variable(size_t vid) : Operand(Operand::VARIABLE), _vid(vid) { }

        void print(std::ostream& out) const override {
            out << '&' << _vid;
        }
    };
}

#endif //IKARUS_VALUE_HPP