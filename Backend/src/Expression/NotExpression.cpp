//
// Created by Bjarne on 06.03.2016.
//

#include "NotExpression.hpp"
#include "ExpressionVisitor.hpp"

namespace ik {
    NotExpression::NotExpression(const Value* value) : UnaryExpression(value) { }

    void NotExpression::accept(ExpressionVisitor* v) const {
        v->visit(this);
    }
}