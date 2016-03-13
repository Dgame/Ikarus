#include "DivideExpression.hpp"
#include "Visitor.hpp"

DivideExpression* DivideExpression::clone() const {
    return new DivideExpression(this->getLeftExpression()->clone(), this->getRightExpression()->clone());
}

void DivideExpression::accept(Visitor& v) {
    v.visit(this);
}
