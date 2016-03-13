#include "NotExpression.hpp"
#include "Visitor.hpp"

void NotExpression::accept(Visitor& v) {
    v.visit(this);
}
