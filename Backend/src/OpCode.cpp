//
// Created by Randy on 05.03.2016.
//

#include "../include/OpCode.hpp"

namespace ik {
    OpCode::OpCode(Type type, Value* value) : _type(type), _value(value) { }
}