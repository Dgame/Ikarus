//
// Created by Randy on 06.03.2016.
//

#include "../../include/Visitor/MathExpressionVisitor.hpp"
#include "../../include/Expression/AddExpression.hpp"
#include "../../include/util.hpp"

namespace ik {
    void MathExpressionVisitor::visit(const AddExpression* expr) {
        const IntegerValue* iv_lhs = expr->getLeft()->isInteger();
        enforce(iv_lhs != nullptr, "...");

        const IntegerValue* iv_rhs = expr->getRight()->isInteger();
        enforce(iv_rhs != nullptr, "...");

        _value = iv_lhs->getValue() + iv_rhs->getValue();
    }
}