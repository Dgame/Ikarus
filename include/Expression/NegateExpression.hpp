#ifndef IKARUS_NEG_EXPRESSION_HPP
#define IKARUS_NEG_EXPRESSION_HPP

#include "UnaryExpression.hpp"

class NegateExpression : public UnaryExpression {
public:
    using UnaryExpression::UnaryExpression;

    NegateExpression* clone() const override {
        return new NegateExpression(this->getExpression()->clone());
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_NEG_EXPRESSION_HPP
