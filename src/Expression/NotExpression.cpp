#include "NotExpression.hpp"
#include "Visitor.hpp"

NotExpression* NotExpression::clone() const {
    return new NotExpression(this->getExpression()->clone());
}

void NotExpression::accept(Visitor& v) {
    v.visit(this);
}
