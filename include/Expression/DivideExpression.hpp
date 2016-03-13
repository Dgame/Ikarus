#ifndef IKARUS_DIVEXPRESSION_HPP
#define IKARUS_DIVEXPRESSION_HPP

#include "BinaryExpression.hpp"

class DivideExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    virtual void accept(Visitor&);
};

#endif //IKARUS_DIVEXPRESSION_HPP
