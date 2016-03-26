#ifndef IKARUS_SUB_EXPRESSION_HPP
#define IKARUS_SUB_EXPRESSION_HPP

#include "BinaryExpression.hpp"

class SubtractExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    SubtractExpression* clone() const override {
        return new SubtractExpression(this->getLeftExpression()->clone(), this->getRightExpression()->clone());
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_SUB_EXPRESSION_HPP
