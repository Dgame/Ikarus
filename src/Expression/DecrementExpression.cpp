#include "DecrementExpression.hpp"
#include "Visitor.hpp"

DecrementExpression* DecrementExpression::clone() const {
    return new DecrementExpression(this->getExpression()->clone());
}

void DecrementExpression::accept(Visitor& v) {
    v.visit(this);
}