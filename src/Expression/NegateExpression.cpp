#include "NegateExpression.hpp"
#include "Visitor.hpp"

void NegateExpression::accept(Visitor& v) {
    v.visit(this);
}
