#ifndef IKARUS_NOT_EQUAL_EXPRESSION_HPP
#define IKARUS_NOT_EQUAL_EXPRESSION_HPP

#include "BinaryExpression.hpp"

class NotEqualExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    NotEqualExpression* clone() const override {
        return new NotEqualExpression(this->getLeftExpression()->clone(), this->getRightExpression()->clone());
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_NOT_EQUAL_EXPRESSION_HPP
