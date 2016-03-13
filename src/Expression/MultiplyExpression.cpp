#include "MultiplyExpression.hpp"
#include "Visitor.hpp"

MultiplyExpression* MultiplyExpression::clone() const {
    return new MultiplyExpression(this->getLeftExpression()->clone(), this->getRightExpression()->clone());
}

void MultiplyExpression::accept(Visitor& v) {
    v.visit(this);
}
