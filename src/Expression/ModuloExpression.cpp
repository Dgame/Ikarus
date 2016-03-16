#include "ModuloExpression.hpp"
#include "Visitor.hpp"

ModuloExpression* ModuloExpression::clone() const {
    return new ModuloExpression(this->getLeftExpression()->clone(), this->getRightExpression()->clone());
}

void ModuloExpression::accept(Visitor& v) {
    v.visit(this);
}
