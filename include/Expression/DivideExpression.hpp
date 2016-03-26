#ifndef IKARUS_DIV_EXPRESSION_HPP
#define IKARUS_DIV_EXPRESSION_HPP

#include "BinaryExpression.hpp"

class DivideExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    DivideExpression* clone() const override {
        return new DivideExpression(this->getLeftExpression()->clone(), this->getRightExpression()->clone());
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_DIV_EXPRESSION_HPP
