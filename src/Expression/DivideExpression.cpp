#include "DivideExpression.hpp"
#include "Visitor.hpp"

void DivideExpression::accept(Visitor& v) {
    v.visit(this);
}
