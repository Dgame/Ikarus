#ifndef IKARUS_DIVEXPRESSION_HPP
#define IKARUS_DIVEXPRESSION_HPP

#include "BinaryExpression.hpp"

class DivideExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    virtual DivideExpression* clone() const;

    virtual void accept(Visitor&);
};

#endif //IKARUS_DIVEXPRESSION_HPP
