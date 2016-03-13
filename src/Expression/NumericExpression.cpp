#include "NumericExpression.hpp"
#include "Visitor.hpp"

NumericExpression::NumericExpression(f32_t num) : _number(num) { }

void NumericExpression::accept(Visitor& v) {
    v.visit(this);
}