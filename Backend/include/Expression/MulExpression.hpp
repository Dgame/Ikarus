//
// Created by Bjarne on 06.03.2016.
//

#ifndef IKARUS_MULEXPRESSION_HPP
#define IKARUS_MULEXPRESSION_HPP

#include "BinaryExpression.hpp"

class MulExpression : public BinaryExpression {
public:
    explicit MulExpression(const Value*, const Value*);

    virtual void accept(ExpressionVisitor*) const;
};

#endif //IKARUS_MULEXPRESSION_HPP
