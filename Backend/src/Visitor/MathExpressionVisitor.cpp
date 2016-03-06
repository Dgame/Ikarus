//
// Created by Randy on 06.03.2016.
//

#include <MathExpressionVisitor.hpp>
#include <AddExpression.hpp>

namespace ik {
    void MathExpressionVisitor::visit(const AddExpression* expr) {
        const NumericValue* iv_lhs = expr->getLeft()->isNumeric();
        enforce(iv_lhs != nullptr, "...");

        const NumericValue* iv_rhs = expr->getRight()->isNumeric();
        enforce(iv_rhs != nullptr, "...");

        _value = iv_lhs->getValue() + iv_rhs->getValue();
    }
}