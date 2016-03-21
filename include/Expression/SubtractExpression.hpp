#ifndef IKARUS_SUBEXPRESSION_HPP
#define IKARUS_SUBEXPRESSION_HPP

#include "BinaryExpression.hpp"

class SubtractExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    virtual SubtractExpression* clone() const override;

    virtual void accept(Visitor&) override;
};

#endif //IKARUS_SUBEXPRESSION_HPP
