#include "NegateExpression.hpp"
#include "Visitor.hpp"

NegateExpression* NegateExpression::clone() const {
    return new NegateExpression(this->getExpression()->clone());
}

void NegateExpression::accept(Visitor& v) {
    v.visit(this);
}
