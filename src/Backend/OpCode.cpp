#include "OpCode.hpp"

namespace Backend {
    OpCode::OpCode(Type type, Expression *exp) : _type(type), _expr(exp) { }
}