#ifndef IKARUS_MUL_EXPRESSION_HPP
#define IKARUS_MUL_EXPRESSION_HPP

#include "BinaryExpression.hpp"

class MultiplyExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    MultiplyExpression* clone() const override {
        return new MultiplyExpression(this->getLeftExpression()->clone(), this->getRightExpression()->clone());
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_MUL_EXPRESSION_HPP
