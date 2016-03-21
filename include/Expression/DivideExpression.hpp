#ifndef IKARUS_DIVEXPRESSION_HPP
#define IKARUS_DIVEXPRESSION_HPP

#include "BinaryExpression.hpp"

class DivideExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    virtual DivideExpression* clone() const override;

    virtual void accept(Visitor&) override;
};

#endif //IKARUS_DIVEXPRESSION_HPP
