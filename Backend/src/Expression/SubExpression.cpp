//
// Created by Bjarne on 06.03.2016.
//

#include "SubExpression.hpp"
#include <ExpressionVisitor.hpp>

SubExpression::SubExpression(const Value* lhs, const Value* rhs) : BinaryExpression(lhs, rhs) { }

void SubExpression::accept(ExpressionVisitor* v) const {
    v->visit(this);
}
