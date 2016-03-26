#ifndef IKARUS_GREATER_EQUAL_EXPRESSION_HPP
#define IKARUS_GREATER_EQUAL_EXPRESSION_HPP

#include "BinaryExpression.hpp"

class GreaterEqualExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    GreaterEqualExpression* clone() const override {
        return new GreaterEqualExpression(this->getLeftExpression()->clone(), this->getRightExpression()->clone());
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_GREATER_EQUAL_EXPRESSION_HPP
