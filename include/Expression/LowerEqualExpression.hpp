#ifndef IKARUS_LOWER_EQUAL_EXPRESSION_HPP
#define IKARUS_LOWER_EQUAL_EXPRESSION_HPP

#include "BinaryExpression.hpp"

class LowerEqualExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    LowerEqualExpression* clone() const override {
        return new LowerEqualExpression(this->getLeftExpression()->clone(), this->getRightExpression()->clone());
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_LOWER_EQUAL_EXPRESSION_HPP
