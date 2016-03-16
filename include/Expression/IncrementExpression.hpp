#ifndef IKARUS_INCEXPRESSION_HPP
#define IKARUS_INCEXPRESSION_HPP

#include "UnaryExpression.hpp"

class IncrementExpression : public UnaryExpression {
public:
    using UnaryExpression::UnaryExpression;

    virtual IncrementExpression* clone() const;

    virtual void accept(Visitor&);
};

#endif //IKARUS_INCEXPRESSION_HPP
