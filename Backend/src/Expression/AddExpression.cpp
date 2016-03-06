//
// Created by Randy on 06.03.2016.
//

#include <AddExpression.hpp>
#include <ExpressionVisitor.hpp>

namespace ik {
    AddExpression::AddExpression(const Value* lhs, const Value* rhs) : _left(lhs), _right(rhs) { }

    void AddExpression::accept(ExpressionVisitor* v) const {
        v->visit(this);
    }
}