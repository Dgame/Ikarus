#include "SubtractExpression.hpp"
#include "Visitor.hpp"

SubtractExpression* SubtractExpression::clone() const {
    return new SubtractExpression(this->getLeftExpression()->clone(), this->getRightExpression()->clone());
}

void SubtractExpression::accept(Visitor& v) {
    v.visit(this);
}
