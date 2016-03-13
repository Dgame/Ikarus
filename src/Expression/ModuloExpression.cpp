#include "ModuloExpression.hpp"
#include "Visitor.hpp"

void ModuloExpression::accept(Visitor& v) {
    v.visit(this);
}
