//
// Created by Bjarne on 06.03.2016.
//

#ifndef IKARUS_DIVEXPRESSION_HPP
#define IKARUS_DIVEXPRESSION_HPP

#include "BinaryExpression.hpp"

class DivExpression : public BinaryExpression {
public:
    explicit DivExpression(const Value*, const Value*);

    virtual void accept(ExpressionVisitor*) const;
};

#endif //IKARUS_DIVEXPRESSION_HPP
