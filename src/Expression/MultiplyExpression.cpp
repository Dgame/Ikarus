#include "MultiplyExpression.hpp"
#include "Visitor.hpp"

void MultiplyExpression::accept(Visitor& v) {
    v.visit(this);
}
