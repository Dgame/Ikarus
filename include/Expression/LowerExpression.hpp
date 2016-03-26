#ifndef IKARUS_LOWER_EXPRESSION_HPP
#define IKARUS_LOWER_EXPRESSION_HPP

#include "BinaryExpression.hpp"

class LowerExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    LowerExpression* clone() const override {
        return new LowerExpression(this->getLeftExpression()->clone(), this->getRightExpression()->clone());
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_LOWER_EXPRESSION_HPP
