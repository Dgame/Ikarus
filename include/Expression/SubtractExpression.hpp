#ifndef IKARUS_SUBEXPRESSION_HPP
#define IKARUS_SUBEXPRESSION_HPP

#include "BinaryExpression.hpp"

class SubtractExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    virtual SubtractExpression* clone() const;

    virtual void accept(Visitor&);
};

#endif //IKARUS_SUBEXPRESSION_HPP
