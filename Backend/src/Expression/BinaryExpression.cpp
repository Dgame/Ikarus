//
// Created by Bjarne on 06.03.2016.
//

#include "BinaryExpression.hpp"

namespace ik {
    BinaryExpression::BinaryExpression(const Value* lhs, const Value* rhs) : _left(lhs), _right(rhs) { }
}
