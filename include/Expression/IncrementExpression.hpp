#ifndef IKARUS_INC_EXPRESSION_HPP
#define IKARUS_INC_EXPRESSION_HPP

#include "UnaryExpression.hpp"

class IncrementExpression : public UnaryExpression {
public:
    using UnaryExpression::UnaryExpression;

    IncrementExpression* clone() const override {
        return new IncrementExpression(this->getExpression()->clone());
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_INC_EXPRESSION_HPP
