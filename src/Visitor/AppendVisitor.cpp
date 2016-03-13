#include "AppendVisitor.hpp"
#include "NumericExpression.hpp"
#include "ArrayExpression.hpp"

void AppendVisitor::visit(NumericExpression* ie) {
    _array = new ArrayExpression();
    _array->assign(ie->clone());
}

void AppendVisitor::visit(ArrayExpression* av) {
    _array = av;
}