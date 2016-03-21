#ifndef IKARUS_INCEXPRESSION_HPP
#define IKARUS_INCEXPRESSION_HPP

#include "UnaryExpression.hpp"

class IncrementExpression : public UnaryExpression {
public:
    using UnaryExpression::UnaryExpression;

    virtual IncrementExpression* clone() const override;

    virtual void accept(Visitor&) override;
};

#endif //IKARUS_INCEXPRESSION_HPP
