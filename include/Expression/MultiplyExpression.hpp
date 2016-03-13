#ifndef IKARUS_MULEXPRESSION_HPP
#define IKARUS_MULEXPRESSION_HPP

#include "BinaryExpression.hpp"

class MultiplyExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    virtual MultiplyExpression* clone() const;

    virtual void accept(Visitor&);
};

#endif //IKARUS_MULEXPRESSION_HPP
