//
// Created by Randy on 05.03.2016.
//

#ifndef IKARUS_OPCODE_HPP
#define IKARUS_OPCODE_HPP

#include <memory>
#include "Value/Value.hpp"

namespace ik {
    class OpCode {
    public:
        enum Type {
            NONE,
            VARIABLE,
            OFFSET,
            VALUE
        };

    private:
        Type _type;
        std::unique_ptr<Value> _value;

    public:
        explicit OpCode(Type, Value*);

        const Type getType() const {
            return _type;
        }

        const Value* getValue() const {
            return _value.get();
        }
    };
}

#endif //IKARUS_OPCODE_HPP
