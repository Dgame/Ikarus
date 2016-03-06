//
// Created by Bjarne on 06.03.2016.
//

#include "DecExpression.hpp"
#include "ExpressionVisitor.hpp"

DecExpression::DecExpression(const Value* value) : UnaryExpression(value) { }

void DecExpression::accept(ExpressionVisitor* v) const {
    v->visit(this);
}