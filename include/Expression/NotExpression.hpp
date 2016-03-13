#ifndef IKARUS_NOTEXPRESSION_HPP
#define IKARUS_NOTEXPRESSION_HPP

#include "UnaryExpression.hpp"

class NotExpression : public UnaryExpression {
public:
    using UnaryExpression::UnaryExpression;

    virtual void accept(Visitor&);
};

#endif //IKARUS_NOTEXPRESSION_HPP
