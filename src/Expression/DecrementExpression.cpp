#include "DecrementExpression.hpp"
#include "Visitor.hpp"

void DecrementExpression::accept(Visitor& v) {
    v.visit(this);
}