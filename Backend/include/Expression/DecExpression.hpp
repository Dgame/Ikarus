//
// Created by Bjarne on 06.03.2016.
//

#ifndef IKARUS_DECEXPRESSION_HPP
#define IKARUS_DECEXPRESSION_HPP

#include "UnaryExpression.hpp"

class DecExpression : public UnaryExpression {
public:
    explicit DecExpression(const Value*);

    virtual void accept(ExpressionVisitor*) const;
};

#endif //IKARUS_DECEXPRESSION_HPP
