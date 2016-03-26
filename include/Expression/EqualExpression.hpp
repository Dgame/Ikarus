#ifndef IKARUS_EQUAL_EXPRESSION_HPP
#define IKARUS_EQUAL_EXPRESSION_HPP

#include "BinaryExpression.hpp"

class EqualExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    EqualExpression* clone() const override {
        return new EqualExpression(this->getLeftExpression()->clone(), this->getRightExpression()->clone());
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_EQUAL_EXPRESSION_HPP
