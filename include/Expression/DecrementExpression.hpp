#ifndef IKARUS_DECEXPRESSION_HPP
#define IKARUS_DECEXPRESSION_HPP

#include "UnaryExpression.hpp"

class DecrementExpression : public UnaryExpression {
public:
    using UnaryExpression::UnaryExpression;

    virtual void accept(Visitor&);
};

#endif //IKARUS_DECEXPRESSION_HPP
