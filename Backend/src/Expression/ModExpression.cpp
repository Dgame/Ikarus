//
// Created by Bjarne on 06.03.2016.
//

#include "ModExpression.hpp"
#include <ExpressionVisitor.hpp>

namespace ik {
    ModExpression::ModExpression(const Value* lhs, const Value* rhs) : BinaryExpression(lhs, rhs) { }

    void ModExpression::accept(ExpressionVisitor* v) const {
        v->visit(this);
    }
}