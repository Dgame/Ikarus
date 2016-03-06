//
// Created by Bjarne on 06.03.2016.
//

#include "MulExpression.hpp"
#include <ExpressionVisitor.hpp>

namespace ik {
    MulExpression::MulExpression(const Value* lhs, const Value* rhs) : BinaryExpression(lhs, rhs) { }

    void MulExpression::accept(ExpressionVisitor* v) const {
        v->visit(this);
    }
}