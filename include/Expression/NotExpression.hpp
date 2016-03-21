#ifndef IKARUS_NOTEXPRESSION_HPP
#define IKARUS_NOTEXPRESSION_HPP

#include "UnaryExpression.hpp"

class NotExpression : public UnaryExpression {
public:
    using UnaryExpression::UnaryExpression;

    virtual NotExpression* clone() const override;

    virtual void accept(Visitor&) override;
};

#endif //IKARUS_NOTEXPRESSION_HPP
