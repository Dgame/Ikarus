#ifndef IKARUS_DECEXPRESSION_HPP
#define IKARUS_DECEXPRESSION_HPP

#include "UnaryExpression.hpp"

class DecrementExpression : public UnaryExpression {
public:
    using UnaryExpression::UnaryExpression;

    virtual DecrementExpression* clone() const override;

    virtual void accept(Visitor&) override;
};

#endif //IKARUS_DECEXPRESSION_HPP
