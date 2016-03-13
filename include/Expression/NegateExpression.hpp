#ifndef IKARUS_NEGEXPRESSION_HPP
#define IKARUS_NEGEXPRESSION_HPP

#include "UnaryExpression.hpp"

class NegateExpression : public UnaryExpression {
public:
    using UnaryExpression::UnaryExpression;

    virtual void accept(Visitor&);
};

#endif //IKARUS_NEGEXPRESSION_HPP
