#include "MathVisitor.hpp"
#include "NumericExpression.hpp"
#include "NotExpression.hpp"
#include "NegateExpression.hpp"
#include "AddExpression.hpp"
#include "SubtractExpression.hpp"
#include "MultiplyExpression.hpp"
#include "DivideExpression.hpp"
#include "ModuloExpression.hpp"
#include "IncrementExpression.hpp"
#include "DecrementExpression.hpp"

#include "util.hpp"
#include <cmath>

void MathVisitor::visit(NumericExpression* exp) {
    _value = exp->getNumber();
}

void MathVisitor::visit(NotExpression* exp) {
    exp->getExpression()->accept(*this);

    _value = !_value;
}

void MathVisitor::visit(NegateExpression* exp) {
    exp->getExpression()->accept(*this);

    _value = _value * -1;
}

void MathVisitor::visit(AddExpression* exp) {
    exp->getLeftExpression()->accept(*this);
    const f32_t lhs = _value;

    exp->getRightExpression()->accept(*this);
    const f32_t rhs = _value;

    _value = lhs + rhs;
}

void MathVisitor::visit(SubtractExpression* exp) {
    exp->getLeftExpression()->accept(*this);
    const f32_t lhs = _value;

    exp->getRightExpression()->accept(*this);
    const f32_t rhs = _value;

    _value = lhs - rhs;
}

void MathVisitor::visit(MultiplyExpression* exp) {
    exp->getLeftExpression()->accept(*this);
    const f32_t lhs = _value;

    exp->getRightExpression()->accept(*this);
    const f32_t rhs = _value;

    _value = lhs * rhs;
}

void MathVisitor::visit(DivideExpression* exp) {
    exp->getLeftExpression()->accept(*this);
    const f32_t lhs = _value;

    exp->getRightExpression()->accept(*this);
    const f32_t rhs = _value;

    _value = lhs / rhs;
}

void MathVisitor::visit(ModuloExpression* exp) {
    exp->getLeftExpression()->accept(*this);
    const f32_t lhs = _value;

    exp->getRightExpression()->accept(*this);
    const f32_t rhs = _value;

    _value = std::fmod(lhs, rhs);
}

void MathVisitor::visit(IncrementExpression* exp) {
    exp->getExpression()->accept(*this);

    _value = _value + 1;
}

void MathVisitor::visit(DecrementExpression* exp) {
    exp->getExpression()->accept(*this);

    _value = _value - 1;
}