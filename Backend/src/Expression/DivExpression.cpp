//
// Created by Bjarne on 06.03.2016.
//

#include "DivExpression.hpp"
#include <ExpressionVisitor.hpp>

namespace ik {
    DivExpression::DivExpression(const Value* lhs, const Value* rhs) : BinaryExpression(lhs, rhs) { }

    void DivExpression::accept(ExpressionVisitor* v) const {
        v->visit(this);
    }
}