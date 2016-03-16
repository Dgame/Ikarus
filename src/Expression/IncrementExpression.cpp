#include "IncrementExpression.hpp"
#include "Visitor.hpp"

IncrementExpression* IncrementExpression::clone() const {
    return new IncrementExpression(this->getExpression()->clone());
}

void IncrementExpression::accept(Visitor& v) {
    v.visit(this);
}
