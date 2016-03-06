//
// Created by Randy on 06.03.2016.
//

#include "../../include/Expression/AddExpression.hpp"
#include "../../include/Visitor/ExpressionVisitor.hpp"

namespace ik {
    AddExpression::AddExpression(const Value* lhs, const Value* rhs) : _left(lhs), _right(rhs) { }

    void AddExpression::accept(ExpressionVisitor* v) const {
        v->visit(this);
    }
}