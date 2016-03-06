//
// Created by Bjarne on 06.03.2016.
//

#ifndef IKARUS_SUBEXPRESSION_HPP
#define IKARUS_SUBEXPRESSION_HPP

#include "BinaryExpression.hpp"

class SubExpression : public BinaryExpression {
public:
    explicit SubExpression(const Value*, const Value*);

    virtual void accept(ExpressionVisitor*) const;
};

#endif //IKARUS_SUBEXPRESSION_HPP
