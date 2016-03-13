#include "IncrementExpression.hpp"
#include "Visitor.hpp"

void IncrementExpression::accept(Visitor& v) {
    v.visit(this);
}
