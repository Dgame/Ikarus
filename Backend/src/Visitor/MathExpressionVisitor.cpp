//
// Created by Randy on 06.03.2016.
//

#include "MathExpressionVisitor.hpp"
#include "NumericValueVisitor.hpp"
#include "AddExpression.hpp"
#include "SubExpression.hpp"
#include "MulExpression.hpp"
#include "DivExpression.hpp"
#include "ModExpression.hpp"
#include "NotExpression.hpp"
#include "NegExpression.hpp"
#include "IncExpression.hpp"
#include "DecExpression.hpp"
#include "NumericValue.hpp"

void MathExpressionVisitor::visit(const AddExpression* expr) {
    NumericValueVisitor nvv;

    expr->getLeft()->accept(&nvv);
    const f32_t lhs = nvv.getNumber();

    expr->getRight()->accept(&nvv);
    const f32_t rhs = nvv.getNumber();

    _value = lhs + rhs;
}

void MathExpressionVisitor::visit(const SubExpression* expr) {
    NumericValueVisitor nvv;

    expr->getLeft()->accept(&nvv);
    const f32_t lhs = nvv.getNumber();

    expr->getRight()->accept(&nvv);
    const f32_t rhs = nvv.getNumber();

    _value = lhs - rhs;
}

void MathExpressionVisitor::visit(const MulExpression* expr) {
    NumericValueVisitor nvv;

    expr->getLeft()->accept(&nvv);
    const f32_t lhs = nvv.getNumber();

    expr->getRight()->accept(&nvv);
    const f32_t rhs = nvv.getNumber();

    _value = lhs * rhs;
}

void MathExpressionVisitor::visit(const DivExpression* expr) {
    NumericValueVisitor nvv;

    expr->getLeft()->accept(&nvv);
    const f32_t lhs = nvv.getNumber();

    expr->getRight()->accept(&nvv);
    const f32_t rhs = nvv.getNumber();

    _value = lhs / rhs;
}

void MathExpressionVisitor::visit(const ModExpression* expr) {
    NumericValueVisitor nvv;

    expr->getLeft()->accept(&nvv);
    const f32_t lhs = nvv.getNumber();

    expr->getRight()->accept(&nvv);
    const f32_t rhs = nvv.getNumber();

    _value = std::fmod(lhs, rhs);
}

void MathExpressionVisitor::visit(const NotExpression* expr) {
    NumericValueVisitor nvv;
    expr->getValue()->accept(&nvv);

    _value = !nvv.getNumber();
}

void MathExpressionVisitor::visit(const NegExpression* expr) {
    NumericValueVisitor nvv;
    expr->getValue()->accept(&nvv);

    _value = nvv.getNumber() * -1;
}

void MathExpressionVisitor::visit(const IncExpression* expr) {
    NumericValueVisitor nvv;
    expr->getValue()->accept(&nvv);

    _value = nvv.getNumber() + 1;
}

void MathExpressionVisitor::visit(const DecExpression* expr) {
    NumericValueVisitor nvv;
    expr->getValue()->accept(&nvv);

    _value = nvv.getNumber() - 1;
}
