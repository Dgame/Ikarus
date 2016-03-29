#include "Backend/VM/Operand.hpp"

namespace Backend {
    Operand Operand::Number(f32_t number) {
        Operand op(Type::NUMBER);
        op._number = number;

        return op;
    }

    Operand Operand::Offset(size_t offset) {
        Operand op(Type::OFFSET);
        op._offset = offset;

        return op;
    }

    Operand Operand::Variable(size_t vid) {
        Operand op(Type::VARIABLE);
        op._vid = vid;

        return op;
    }

    void Operand::print(std::ostream& out) const {
        switch (_type) {
            case NONE:
                break;
            case NUMBER:
                out << _number;
                break;
            case OFFSET:
                out << '~' << _offset;
                break;
            case VARIABLE:
                out << '&' << _vid;
                break;
        }
    }
}