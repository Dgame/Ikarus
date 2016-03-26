#ifndef IKARUS_GREATER_EXPRESSION_HPP
#define IKARUS_GREATER_EXPRESSION_HPP

#include "BinaryExpression.hpp"

class GreaterExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    GreaterExpression* clone() const override {
        return new GreaterExpression(this->getLeftExpression()->clone(), this->getRightExpression()->clone());
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_GREATER_EXPRESSION_HPP
