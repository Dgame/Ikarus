//
// Created by Randy on 05.03.2016.
//

#ifndef IKARUS_OPCODE_HPP
#define IKARUS_OPCODE_HPP

#include <memory>
#include "Value.hpp"

class OpCode {
public:
    enum Type {
        VARIABLE,
        OFFSET,
        VALUE
    };

private:
    Type _type;

    std::unique_ptr<const Value> _value;

public:
    explicit OpCode(Type, const Value*);

    const Type getType() const {
        return _type;
    }

    const Value* getValue() const {
        return _value.get();
    }
};

#endif //IKARUS_OPCODE_HPP
