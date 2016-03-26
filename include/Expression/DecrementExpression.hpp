#ifndef IKARUS_DEC_EXPRESSION_HPP
#define IKARUS_DEC_EXPRESSION_HPP

#include "UnaryExpression.hpp"

class DecrementExpression : public UnaryExpression {
public:
    using UnaryExpression::UnaryExpression;

    DecrementExpression* clone() const override {
        return new DecrementExpression(this->getExpression()->clone());
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_DEC_EXPRESSION_HPP
