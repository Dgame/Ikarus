#ifndef IKARUS_INTEGER_EXPRESSION_HPP
#define IKARUS_INTEGER_EXPRESSION_HPP

#include "BinaryExpression.hpp"

class AddExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    AddExpression* clone() const override {
        return new AddExpression(this->getLeftExpression()->clone(), this->getRightExpression()->clone());
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_INTEGER_EXPRESSION_HPP
