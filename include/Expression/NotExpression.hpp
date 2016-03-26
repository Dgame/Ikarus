#ifndef IKARUS_NOT_EXPRESSION_HPP
#define IKARUS_NOT_EXPRESSION_HPP

#include "UnaryExpression.hpp"

class NotExpression : public UnaryExpression {
public:
    using UnaryExpression::UnaryExpression;

    NotExpression* clone() const override {
        return new NotExpression(this->getExpression()->clone());
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_NOT_EXPRESSION_HPP
