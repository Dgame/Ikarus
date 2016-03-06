//
// Created by Bjarne on 06.03.2016.
//

#include "IncExpression.hpp"
#include "ExpressionVisitor.hpp"

IncExpression::IncExpression(const Value* value) : UnaryExpression(value) { }

void IncExpression::accept(ExpressionVisitor* v) const {
    v->visit(this);
}
