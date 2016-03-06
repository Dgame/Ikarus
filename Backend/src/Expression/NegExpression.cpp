//
// Created by Bjarne on 06.03.2016.
//

#include "NegExpression.hpp"
#include "ExpressionVisitor.hpp"

NegExpression::NegExpression(const Value* value) : UnaryExpression(value) { }

void NegExpression::accept(ExpressionVisitor* v) const {
    v->visit(this);
}
