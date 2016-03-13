#ifndef IKARUS_INTEGEREXPRESSION_HPP
#define IKARUS_INTEGEREXPRESSION_HPP

#include "BinaryExpression.hpp"

class AddExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    virtual AddExpression* clone() const;

    virtual void accept(Visitor&);
};

#endif //IKARUS_INTEGEREXPRESSION_HPP
