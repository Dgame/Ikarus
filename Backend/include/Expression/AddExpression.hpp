//
// Created by Randy on 06.03.2016.
//

#ifndef IKARUS_INTEGEREXPRESSION_HPP
#define IKARUS_INTEGEREXPRESSION_HPP

#include "BinaryExpression.hpp"

class AddExpression : public BinaryExpression {
public:
    explicit AddExpression(const Value*, const Value*);

    virtual void accept(ExpressionVisitor*) const;
};

#endif //IKARUS_INTEGEREXPRESSION_HPP
