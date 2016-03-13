#include "SubtractExpression.hpp"
#include "Visitor.hpp"

void SubtractExpression::accept(Visitor& v) {
    v.visit(this);
}
