//
// Created by Randy on 06.03.2016.
//

#include "MathExpressionVisitor.hpp"
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

#include <cmath>

namespace ik {
    void MathExpressionVisitor::visit(const AddExpression* expr) {
        const NumericValue* iv_lhs = expr->getLeft()->isNumeric();
        enforce(iv_lhs != nullptr, "...");

        const NumericValue* iv_rhs = expr->getRight()->isNumeric();
        enforce(iv_rhs != nullptr, "...");

        _value = iv_lhs->getValue() + iv_rhs->getValue();
    }

    void MathExpressionVisitor::visit(const SubExpression* expr) {
        const NumericValue* iv_lhs = expr->getLeft()->isNumeric();
        enforce(iv_lhs != nullptr, "...");

        const NumericValue* iv_rhs = expr->getRight()->isNumeric();
        enforce(iv_rhs != nullptr, "...");

        _value = iv_lhs->getValue() - iv_rhs->getValue();
    }

    void MathExpressionVisitor::visit(const MulExpression* expr) {
        const NumericValue* iv_lhs = expr->getLeft()->isNumeric();
        enforce(iv_lhs != nullptr, "...");

        const NumericValue* iv_rhs = expr->getRight()->isNumeric();
        enforce(iv_rhs != nullptr, "...");

        _value = iv_lhs->getValue() * iv_rhs->getValue();
    }

    void MathExpressionVisitor::visit(const DivExpression* expr) {
        const NumericValue* iv_lhs = expr->getLeft()->isNumeric();
        enforce(iv_lhs != nullptr, "...");

        const NumericValue* iv_rhs = expr->getRight()->isNumeric();
        enforce(iv_rhs != nullptr, "...");

        _value = iv_lhs->getValue() / iv_rhs->getValue();
    }

    void MathExpressionVisitor::visit(const ModExpression* expr) {
        const NumericValue* iv_lhs = expr->getLeft()->isNumeric();
        enforce(iv_lhs != nullptr, "...");

        const NumericValue* iv_rhs = expr->getRight()->isNumeric();
        enforce(iv_rhs != nullptr, "...");

        _value = std::fmod(iv_lhs->getValue(), iv_rhs->getValue());
    }

    void MathExpressionVisitor::visit(const NotExpression* expr) {
        const NumericValue* value = expr->getValue()->isNumeric();
        enforce(value != nullptr, "...");

        _value = !value->getValue();
    }

    void MathExpressionVisitor::visit(const NegExpression* expr) {
        const NumericValue* value = expr->getValue()->isNumeric();
        enforce(value != nullptr, "...");

        _value = value->getValue() * -1;
    }

    void MathExpressionVisitor::visit(const IncExpression* expr) {
        const NumericValue* value = expr->getValue()->isNumeric();
        enforce(value != nullptr, "...");

        _value = value->getValue() + 1;
    }

    void MathExpressionVisitor::visit(const DecExpression* expr) {
        const NumericValue* value = expr->getValue()->isNumeric();
        enforce(value != nullptr, "...");

        _value = value->getValue() - 1;
    }
}