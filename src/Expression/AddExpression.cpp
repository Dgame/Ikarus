#include "AddExpression.hpp"
#include "Visitor.hpp"

void AddExpression::accept(Visitor& v) {
    v.visit(this);
}
