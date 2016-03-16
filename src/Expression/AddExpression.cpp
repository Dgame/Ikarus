#include "AddExpression.hpp"
#include "Visitor.hpp"

AddExpression* AddExpression::clone() const {
    return new AddExpression(this->getLeftExpression()->clone(), this->getRightExpression()->clone());
}

void AddExpression::accept(Visitor& v) {
    v.visit(this);
}
